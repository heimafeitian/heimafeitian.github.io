#include<stdlib.h>
#include<signal.h>
#include<getopt.h>

#include<rte_eal.h>
#include<rte_ethdev.h>
#include<rte_thash.h>


#define RTE_TEST_RX_DESC_DEFAULT 512
#define RTE_TEST_TX_DESC_DEFAULT 512
static volatile bool force_quit = false;
static uint8_t nb_rx_queue = 1;
static uint16_t listen_port = 61440;
static uint16_t nb_ports_available = 0;

static struct action_rss_data {
    struct rte_flow_action_rss conf;
    uint16_t queue[128];
}rss_data;

static uint8_t rss_key[] = {
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
};

static struct rte_eth_conf port_conf = {
    .rxmode = {
        .mq_mode = ETH_MQ_RX_RSS,
        .max_rx_pkt_len = 9018,
        .split_hdr_size = 0,
        .offloads = DEV_RX_OFFLOAD_IPV4_CKSUM |
                    DEV_RX_OFFLOAD_UDP_CKSUM |
                    DEV_RX_OFFLOAD_TCP_CKSUM |
                    DEV_RX_OFFLOAD_SCATTER |
                    DEV_RX_OFFLOAD_JUMBO_FRAME,
    },
    .rx_adv_conf = {
        .rss_conf = {
            .rss_key = rss_key,
            .rss_key_len = sizeof(rss_key),
            .rss_hf = ETH_RSS_IPV4 | \
	                ETH_RSS_FRAG_IPV4 | \
                    ETH_RSS_NONFRAG_IPV4_OTHER | \
                    ETH_RSS_IPV6 | \
                    ETH_RSS_FRAG_IPV6 | \
                    ETH_RSS_NONFRAG_IPV6_OTHER | \
                    ETH_RSS_NONFRAG_IPV4_UDP | \
	                ETH_RSS_NONFRAG_IPV6_UDP | \
                    ETH_RSS_NONFRAG_IPV4_TCP | \
	                ETH_RSS_NONFRAG_IPV6_TCP,
        },
    },
    .txmode = {
        .mq_mode = ETH_MQ_TX_NONE,
    },
};

static int test_setup_flow(uint16_t proto, uint16_t listen_port, uint16_t portid) {
    struct rte_flow_attr attr = {};
    struct rte_flow_item items[4] = {};
    struct rte_flow_error error = {};
    int ret;

    attr = (const struct rte_flow_attr) {
        .group = 0,
        .priority = 0,
        .ingress = 1,
        .egress = 0,
        .reserved = 0,
    };

    struct rte_flow_item_eth item_eth_spec = {};
    struct rte_flow_item_eth item_eth_mask = {};

    struct rte_flow_item_ipv4 item_ipv4_spec;
    struct rte_flow_item_ipv4 item_ipv4_mask;
    memset(&item_ipv4_spec, 0, sizeof(struct rte_flow_item_ipv4));
    memset(&item_ipv4_mask, 0, sizeof(struct rte_flow_item_ipv4));

    items[0] = (struct rte_flow_item) {
        .type = RTE_FLOW_ITEM_TYPE_ETH,
        .spec = &item_eth_spec,
        .mask = &item_eth_mask,
    };

    items[1] = (struct rte_flow_item) {
        .type = RTE_FLOW_ITEM_TYPE_IPV4,
        .spec = &item_ipv4_spec,
        .mask = &item_ipv4_mask,
    };

    struct rte_flow_item_udp item_udp_spec = {
        .hdr = {
            .src_port = 0,
            .dst_port = htons(listen_port),
         }
    };
    struct rte_flow_item_udp item_udp_mask = {
        .hdr = {
            .src_port = 0,
            .dst_port = 0xFFFF,
        }
    };

    struct rte_flow_item_tcp item_tcp_spec = {
        .hdr = {
            .src_port = 0,
            .dst_port = htons(listen_port),
        }
    };
    struct rte_flow_item_tcp item_tcp_mask = {
        .hdr = {
            .src_port = 0,
            .dst_port = 0xFFFF,
        }
    };

    switch (proto) {
        case IPPROTO_UDP:
            items[2] = (struct rte_flow_item) {
                .type = RTE_FLOW_ITEM_TYPE_UDP,
                .spec = &item_udp_spec,
                .mask = &item_udp_mask,
            };
            break;
        case IPPROTO_TCP:
            items[2] = (struct rte_flow_item) {
                .type = RTE_FLOW_ITEM_TYPE_TCP,
                .spec = &item_tcp_spec,
                .mask = &item_tcp_mask,
            };
            break;
        default: assert(false);
    }

    items[3] = (struct rte_flow_item) {
        .type = RTE_FLOW_ITEM_TYPE_END,
    };

    struct action_rss_data rss_data = {
        .conf = (struct rte_flow_action_rss) {
            .func = RTE_ETH_HASH_FUNCTION_DEFAULT,
            .level = 0,
            .types = port_conf.rx_adv_conf.rss_conf.rss_hf,
            .key_len = sizeof(rss_key),
            .queue_num = nb_rx_queue,
            .key = rss_key,
            .queue = rss_data.queue,
        },
        .queue = { 0 },
    };

    struct rte_flow_action_rss action_rss;
    uint8_t i;
    for (i = 0; i< nb_rx_queue; i++) {
        rss_data.queue[i] = i;
    }
    action_rss = rss_data.conf;

    const struct rte_flow_action actions[] = {
        { RTE_FLOW_ACTION_TYPE_VF,
            &(const struct rte_flow_action_vf) {
                    .original = 1,
                }
        },
        { RTE_FLOW_ACTION_TYPE_RSS,
            &action_rss,
        },
        { RTE_FLOW_ACTION_TYPE_END, NULL},
    };
    
    struct rte_flow *flow;
    flow = rte_flow_create(portid, &attr, items, actions, &error);
    if (flow == NULL) {
        printf("[ERROR] Create flow failed, ret=%d, err=%s\n", ret, error.message);
        return -1;
    }
    return 0;
}

static uint16_t test_check_rss(struct rte_mbuf *m) {
    uint32_t rss_hw, rss_soft;
    rss_hw = m->hash.rss;
    struct rte_ether_hdr *eth = rte_pktmbuf_mtod(m, struct rte_ether_hdr*);
    struct rte_ipv4_hdr *iph = (void *)(eth + 1);
    struct rte_tcp_hdr *tph;
    struct rte_udp_hdr *udh;
    struct rte_ipv4_tuple rss_v4;

    rss_v4.src_addr = rte_be_to_cpu_32(iph->src_addr);
    rss_v4.dst_addr = rte_be_to_cpu_32(iph->dst_addr);
    switch (iph->next_proto_id) {
        case IPPROTO_TCP:
            tph = (void*)iph + ((iph->version_ihl & 0x0f) << 2);
            rss_v4.sport = rte_be_to_cpu_16(tph->src_port);
            rss_v4.dport = rte_be_to_cpu_16(tph->dst_port);
            break;
        case IPPROTO_UDP:
            udh = (void*)iph + ((iph->version_ihl & 0x0f) << 2);
            rss_v4.sport = rte_be_to_cpu_16(udh->src_port);
            rss_v4.dport = rte_be_to_cpu_16(udh->dst_port);
            break;
    }
    rss_soft = rte_softrss((uint32_t *)&rss_v4,
        RTE_THASH_V4_L4_LEN, rss_key);
    printf("\nhw rss 0x%x, soft rss 0x%x\n", rss_hw, rss_soft);
}


static void print_usage() {
    fprintf(stderr, "   -p, listen port\n"
            "   -n, number of rx_queues for each port\n"
            "   -t, setup one tx_queue at least\n");
}

static void signal_handler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n", signum);
        force_quit = true;
    }
}

static void test_main_loop(void) {
    struct rte_mbuf *pkts_burst[256];
    struct rte_mbuf *m;
    unsigned lcore_id;
    uint16_t i, j, k, nb_rx;

    lcore_id = rte_lcore_id();
    if (lcore_id != rte_get_main_lcore()) {
        return;
    }

    while (!force_quit) {
        for (i = 0; i < nb_ports_available; i++) {
            for (j = 0; j < nb_rx_queue; j ++) {
                nb_rx = rte_eth_rx_burst(i, j, pkts_burst, 64);
                if (nb_rx > 0) {
                    for (k = 0; k < nb_rx; k++) {
                        m = pkts_burst[k];
                        rte_prefetch0(rte_pktmbuf_mtod(m, void *));
                        test_check_rss(m);
                        rte_pktmbuf_free(m);
                    }
                }
            }
        }
    }
}

static void disable_broadcast(uint16_t portid) {
    int ret;
    struct rte_ether_addr maddr = {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
    };
    ret = rte_eth_dev_mac_addr_add(portid, &maddr, 0);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Failed to set broadcast mac\n");
    }
    ret = rte_eth_dev_mac_addr_remove(portid, &maddr);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Failed to remove broadcast mac\n");
    }
}

int main(int argc, char **argv) {
    int ret, nb_ports;
    uint16_t nb_rxd = RTE_TEST_RX_DESC_DEFAULT, nb_txd = RTE_TEST_TX_DESC_DEFAULT;
    uint16_t portid;

    struct rte_mempool *pktmbuf_pool;

    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Invalid EAL arguments\n");
    }
    argc -= ret;
    argv += ret;

    uint32_t nb_tx_queue = 1;
    int ch;
    while ((ch = getopt(argc, argv, "p:n:t:")) != -1) {
        switch (ch) {
            case 'p':
                sscanf(optarg, "%hu", &listen_port);
                break;
            case 'n':
                sscanf(optarg, "%hhu", &nb_rx_queue);
                break;
            case 't':
                sscanf(optarg, "%u", &nb_tx_queue);
                break;
            default:
                print_usage();
                break;
        }
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports == 0) {
        rte_exit(EXIT_FAILURE, "No Ethernet ports - bye\n");
    }

    pktmbuf_pool = rte_pktmbuf_pool_create(
        "mbuf_pool", 8192U, 256, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id()
    );

    RTE_ETH_FOREACH_DEV(portid) {
        struct rte_eth_rxconf rxq_conf;
        struct rte_eth_txconf txq_conf;
        struct rte_eth_conf local_port_conf = port_conf;
        struct rte_eth_dev_info dev_info;

        rte_eth_dev_info_get(portid, &dev_info);

        if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE) {
            local_port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;
        }
        struct rte_flow_error error;
        ret = rte_eth_dev_configure(portid, nb_rx_queue, nb_tx_queue, &port_conf);
        ret = rte_flow_isolate(portid, 1, &error);
        if (ret != 0) {
            printf("[WARNING] flow isolate failed\n");
        }
        rte_eth_promiscuous_disable(portid);
        rte_eth_allmulticast_disable(portid);

        ret = rte_eth_dev_adjust_nb_rx_tx_desc(portid, &nb_rxd, &nb_txd);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot adjust number of descriptors: err=%d, port=%u\n",
                     ret, portid);
        }
        rxq_conf = dev_info.default_rxconf;
        rxq_conf.offloads = local_port_conf.rxmode.offloads;
        uint16_t i;
        for (i = 0; i < nb_rx_queue; i++) {
            ret = rte_eth_rx_queue_setup(portid, i, nb_rxd, rte_eth_dev_socket_id(portid),
                                     &rxq_conf, pktmbuf_pool);
            if (ret < 0) {
                rte_exit(EXIT_FAILURE, "rte_eth_rx_queue_setup:err=%d, port=%u\n",
                        ret, portid);
            }
        }
        txq_conf = dev_info.default_txconf;
        for (i = 0; i < nb_tx_queue; i++) {
            ret = rte_eth_tx_queue_setup(portid, i, nb_txd, rte_eth_dev_socket_id(portid),
                                     &txq_conf);
            if (ret < 0) {
                rte_exit(EXIT_FAILURE, "rte_eth_tx_queue_setup:err=%d, port=%u\n",
                        ret, portid);
            }
        }
        
        ret = rte_eth_dev_start(portid);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "rte_eth_dev_start:err=%d, port=%u\n", ret, portid);
        }

        disable_broadcast(portid);

        ret = test_setup_flow(IPPROTO_UDP, listen_port, portid);
        if (ret != 0) {
            printf("[ERROR] setup udp flow failed\n");
            exit(-1);
        }
        ret = test_setup_flow(IPPROTO_TCP, listen_port, portid);
        if (ret != 0) {
            printf("[ERROR] setup tcp flow failed\n");
            exit(-1);
        }
        nb_ports_available++;
    }
    test_main_loop();
    RTE_ETH_FOREACH_DEV(portid) {
        rte_eth_dev_stop(portid);
        rte_eth_dev_close(portid);
    }
    printf("Bye...\n");
    return ret;
}
