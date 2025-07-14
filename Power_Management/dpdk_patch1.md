From patchwork Fri Jul 15 13:12:53 2022
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Burakov, Anatoly" <anatoly.burakov@intel.com>
X-Patchwork-Id: 113984
X-Patchwork-Delegate: thomas@monjalon.net
Return-Path: <dev-bounces@dpdk.org>
X-Original-To: patchwork@inbox.dpdk.org
Delivered-To: patchwork@inbox.dpdk.org
Received: from mails.dpdk.org (mails.dpdk.org [217.70.189.124])
	by inbox.dpdk.org (Postfix) with ESMTP id 4AF12A0032;
	Fri, 15 Jul 2022 15:13:20 +0200 (CEST)
Received: from [217.70.189.124] (localhost [127.0.0.1])
	by mails.dpdk.org (Postfix) with ESMTP id 2ED1D41156;
	Fri, 15 Jul 2022 15:13:20 +0200 (CEST)
Received: from mga06.intel.com (mga06b.intel.com [134.134.136.31])
 by mails.dpdk.org (Postfix) with ESMTP id B68F840696
 for <dev@dpdk.org>; Fri, 15 Jul 2022 15:13:17 +0200 (CEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
 d=intel.com; i=@intel.com; q=dns/txt; s=Intel;
 t=1657890797; x=1689426797;
 h=from:to:cc:subject:date:message-id:mime-version:
 content-transfer-encoding;
 bh=dw7sTu2ZkVn8B04SmlghFK8L/JsaJwLdpyrcROpFfR4=;
 b=Fv4PZz2gur6ePn6fXgH4tbagphGfMTRWTclFmcKQP4ch47dcTGIWK0te
 zYsxwi5kuW4mqlJnczgdS6pAH1kPtns2X8eaE0ugyR4GNj+33lXrfXtTX
 av6djWCx8rwzU/o94TBpadE5sJDRwDawxDvqyzDKoDv9ulysriyIsMz6d
 ELLlwAodf5sVwkdV1mI6eXd7i7cYCfTq7QxssOJ7ToklprlNBEdaHnrmG
 hfx+70duy4HEKd2cMzrTUdr0RMwzolW3r7tqstT0y9b2chyP/PWpZcqJO
 Fo82UoRse5t8i1M+7WIC/mkrIt311RADCY5l4xWrg20v8lg/h2DN8xOrL g==;
X-IronPort-AV: E=McAfee;i="6400,9594,10408"; a="347467263"
X-IronPort-AV: E=Sophos;i="5.92,274,1650956400"; d="scan'208";a="347467263"
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
 by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2022 06:13:00 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.92,274,1650956400"; d="scan'208";a="685956355"
Received: from silpixa00401191.ir.intel.com ([10.55.128.75])
 by FMSMGA003.fm.intel.com with ESMTP; 15 Jul 2022 06:12:55 -0700
From: Anatoly Burakov <anatoly.burakov@intel.com>
To: dev@dpdk.org, Bruce Richardson <bruce.richardson@intel.com>,
 Nicolas Chautru <nicolas.chautru@intel.com>,
 Fiona Trahe <fiona.trahe@intel.com>,
 Ashish Gupta <ashish.gupta@marvell.com>,
 Declan Doherty <declan.doherty@intel.com>,
 David Hunt <david.hunt@intel.com>, Ray Kinsella <mdr@ashroe.eu>,
 Neil Horman <nhorman@tuxdriver.com>, Thomas Monjalon <thomas@monjalon.net>,
 Ferruh Yigit <ferruh.yigit@intel.com>,
 Andrew Rybchenko <andrew.rybchenko@oktetlabs.ru>,
 Jerin Jacob <jerinj@marvell.com>, Nipun Gupta <nipun.gupta@nxp.com>,
 Hemant Agrawal <hemant.agrawal@nxp.com>, Ori Kam <orika@nvidia.com>,
 Honnappa Nagarahalli <honnappa.nagarahalli@arm.com>,
 Konstantin Ananyev <konstantin.ananyev@intel.com>
Cc: Kevin Laatz <kevin.laatz@intel.com>,
	Conor Walsh <conor.walsh@intel.com>
Subject: [20.11 PATCH v1 1/2] eal: add lcore busyness telemetry
Date: Fri, 15 Jul 2022 13:12:53 +0000
Message-Id: 
 <eab9994ef9e9531e6ed03773a1ecd2654a196a3d.1657890738.git.anatoly.burakov@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-BeenThere: dev@dpdk.org
X-Mailman-Version: 2.1.29
Precedence: list
List-Id: DPDK patches and discussions <dev.dpdk.org>
List-Unsubscribe: <https://mails.dpdk.org/options/dev>,
 <mailto:dev-request@dpdk.org?subject=unsubscribe>
List-Archive: <http://mails.dpdk.org/archives/dev/>
List-Post: <mailto:dev@dpdk.org>
List-Help: <mailto:dev-request@dpdk.org?subject=help>
List-Subscribe: <https://mails.dpdk.org/listinfo/dev>,
 <mailto:dev-request@dpdk.org?subject=subscribe>
Errors-To: dev-bounces@dpdk.org

Currently, there is no way to measure lcore busyness in a passive way,
without any modifications to the application. This patch adds a new EAL
API that will be able to passively track core busyness.

The busyness is calculated by relying on the fact that most DPDK API's
will poll for packets. Empty polls can be counted as "idle", while
non-empty polls can be counted as busy. To measure lcore busyness, we
simply call the telemetry timestamping function with the number of polls
a particular code section has processed, and count the number of cycles
we've spent processing empty bursts. The more empty bursts we encounter,
the less cycles we spend in "busy" state, and the less core busyness
will be reported.

In order for all of the above to work without modifications to the
application, the library code needs to be instrumented with calls to
the lcore telemetry busyness timestamping function. The following parts
of DPDK are instrumented with lcore telemetry calls:

- All major driver API's:
  - ethdev
  - cryptodev
  - compressdev
  - regexdev
  - bbdev
  - rawdev
  - eventdev
- Some additional libraries:
  - ring
  - distributor

To avoid performance impact from having lcore telemetry support, a
global variable is exported by EAL, and a call to timestamping function
is wrapped into a macro, so that whenever telemetry is disabled, it only
takes one additional branch and no function calls are performed. It is
also possible to disable it at compile time by commenting out
RTE_LCORE_BUSYNESS from build config.

This patch also adds a telemetry endpoint to report lcore busyness, as
well as telemetry endpoints to enable/disable lcore telemetry.

Signed-off-by: Kevin Laatz <kevin.laatz@intel.com>
Signed-off-by: Conor Walsh <conor.walsh@intel.com>
Signed-off-by: David Hunt <david.hunt@intel.com>
Signed-off-by: Anatoly Burakov <anatoly.burakov@intel.com>
---
 config/rte_config.h                           |   2 +
 lib/librte_bbdev/rte_bbdev.h                  |  16 +-
 lib/librte_compressdev/rte_compressdev.c      |   2 +
 lib/librte_cryptodev/rte_cryptodev.h          |   2 +
 lib/librte_distributor/rte_distributor.c      |  17 +-
 .../rte_distributor_single.c                  |  10 +-
 .../common/eal_common_lcore_telemetry.c       | 274 ++++++++++++++++++
 lib/librte_eal/common/meson.build             |   2 +
 lib/librte_eal/include/rte_lcore.h            |  80 +++++
 lib/librte_eal/meson.build                    |   3 +
 lib/librte_eal/version.map                    |   7 +
 lib/librte_ethdev/rte_ethdev.h                |   2 +
 lib/librte_eventdev/rte_eventdev.h            |  20 +-
 lib/librte_rawdev/rte_rawdev.c                |   5 +-
 lib/librte_regexdev/rte_regexdev.h            |   5 +-
 lib/librte_ring/rte_ring_elem.h               |   2 +
 16 files changed, 429 insertions(+), 20 deletions(-)
 create mode 100644 lib/librte_eal/common/eal_common_lcore_telemetry.c

diff --git a/config/rte_config.h b/config/rte_config.h
index a0b5160ff2..3531f4ef7b 100644
--- a/config/rte_config.h
+++ b/config/rte_config.h
@@ -40,6 +40,8 @@
 #define RTE_LOG_DP_LEVEL RTE_LOG_INFO
 #define RTE_BACKTRACE 1
 #define RTE_MAX_VFIO_CONTAINERS 64
+#define RTE_LCORE_BUSYNESS 1
+#define RTE_LCORE_BUSYNESS_PERIOD 4000000ULL
 
 /* bsd module defines */
 #define RTE_CONTIGMEM_MAX_NUM_BUFS 64
diff --git a/lib/librte_bbdev/rte_bbdev.h b/lib/librte_bbdev/rte_bbdev.h
index 7017124414..78501ce8ce 100644
--- a/lib/librte_bbdev/rte_bbdev.h
+++ b/lib/librte_bbdev/rte_bbdev.h
@@ -623,7 +623,9 @@ rte_bbdev_dequeue_enc_ops(uint16_t dev_id, uint16_t queue_id,
 {
 	struct rte_bbdev *dev = &rte_bbdev_devices[dev_id];
 	struct rte_bbdev_queue_data *q_data = &dev->data->queues[queue_id];
-	return dev->dequeue_enc_ops(q_data, ops, num_ops);
+	const uint16_t nb_ops = dev->dequeue_enc_ops(q_data, ops, num_ops);
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
+	return nb_ops;
 }
 
 /**
@@ -656,7 +658,9 @@ rte_bbdev_dequeue_dec_ops(uint16_t dev_id, uint16_t queue_id,
 {
 	struct rte_bbdev *dev = &rte_bbdev_devices[dev_id];
 	struct rte_bbdev_queue_data *q_data = &dev->data->queues[queue_id];
-	return dev->dequeue_dec_ops(q_data, ops, num_ops);
+	const uint16_t nb_ops = dev->dequeue_dec_ops(q_data, ops, num_ops);
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
+	return nb_ops;
 }
 
 
@@ -688,7 +692,9 @@ rte_bbdev_dequeue_ldpc_enc_ops(uint16_t dev_id, uint16_t queue_id,
 {
 	struct rte_bbdev *dev = &rte_bbdev_devices[dev_id];
 	struct rte_bbdev_queue_data *q_data = &dev->data->queues[queue_id];
-	return dev->dequeue_ldpc_enc_ops(q_data, ops, num_ops);
+	const uint16_t nb_ops = dev->dequeue_ldpc_enc_ops(q_data, ops, num_ops);
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
+	return nb_ops;
 }
 
 /**
@@ -719,7 +725,9 @@ rte_bbdev_dequeue_ldpc_dec_ops(uint16_t dev_id, uint16_t queue_id,
 {
 	struct rte_bbdev *dev = &rte_bbdev_devices[dev_id];
 	struct rte_bbdev_queue_data *q_data = &dev->data->queues[queue_id];
-	return dev->dequeue_ldpc_dec_ops(q_data, ops, num_ops);
+	const uint16_t nb_ops = dev->dequeue_ldpc_dec_ops(q_data, ops, num_ops);
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
+	return nb_ops;
 }
 
 /** Definitions of device event types */
diff --git a/lib/librte_compressdev/rte_compressdev.c b/lib/librte_compressdev/rte_compressdev.c
index 49a342f400..dfc0f0804d 100644
--- a/lib/librte_compressdev/rte_compressdev.c
+++ b/lib/librte_compressdev/rte_compressdev.c
@@ -582,6 +582,8 @@ rte_compressdev_dequeue_burst(uint8_t dev_id, uint16_t qp_id,
 	nb_ops = (*dev->dequeue_burst)
 			(dev->data->queue_pairs[qp_id], ops, nb_ops);
 
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
+
 	return nb_ops;
 }
 
diff --git a/lib/librte_cryptodev/rte_cryptodev.h b/lib/librte_cryptodev/rte_cryptodev.h
index 0935fd5875..7b89fd9ad7 100644
--- a/lib/librte_cryptodev/rte_cryptodev.h
+++ b/lib/librte_cryptodev/rte_cryptodev.h
@@ -949,6 +949,8 @@ rte_cryptodev_dequeue_burst(uint8_t dev_id, uint16_t qp_id,
 			(dev->data->queue_pairs[qp_id], ops, nb_ops);
 
 	rte_cryptodev_trace_dequeue_burst(dev_id, qp_id, (void **)ops, nb_ops);
+
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
 	return nb_ops;
 }
 
diff --git a/lib/librte_distributor/rte_distributor.c b/lib/librte_distributor/rte_distributor.c
index 07e385a259..45b3a61898 100644
--- a/lib/librte_distributor/rte_distributor.c
+++ b/lib/librte_distributor/rte_distributor.c
@@ -58,6 +58,9 @@ rte_distributor_request_pkt(struct rte_distributor *d,
 
 		while (rte_rdtsc() < t)
 			rte_pause();
+
+		/* this was an empty poll */
+		RTE_LCORE_TELEMETRY_TIMESTAMP(0);
 	}
 
 	/*
@@ -136,24 +139,28 @@ rte_distributor_get_pkt(struct rte_distributor *d,
 
 	if (unlikely(d->alg_type == RTE_DIST_ALG_SINGLE)) {
 		if (return_count <= 1) {
+			uint16_t cnt;
 			pkts[0] = rte_distributor_get_pkt_single(d->d_single,
-				worker_id, return_count ? oldpkt[0] : NULL);
-			return (pkts[0]) ? 1 : 0;
+								 worker_id, return_count ? oldpkt[0] : NULL);
+			cnt = (pkts[0] != NULL) ? 1 : 0;
+			RTE_LCORE_TELEMETRY_TIMESTAMP(cnt);
+			return cnt;
 		} else
 			return -EINVAL;
 	}
 
 	rte_distributor_request_pkt(d, worker_id, oldpkt, return_count);
 
-	count = rte_distributor_poll_pkt(d, worker_id, pkts);
-	while (count == -1) {
+	while ((count = rte_distributor_poll_pkt(d, worker_id, pkts)) == -1) {
 		uint64_t t = rte_rdtsc() + 100;
 
 		while (rte_rdtsc() < t)
 			rte_pause();
 
-		count = rte_distributor_poll_pkt(d, worker_id, pkts);
+		/* this was an empty poll */
+		RTE_LCORE_TELEMETRY_TIMESTAMP(0);
 	}
+	RTE_LCORE_TELEMETRY_TIMESTAMP(count);
 	return count;
 }
 
diff --git a/lib/librte_distributor/rte_distributor_single.c b/lib/librte_distributor/rte_distributor_single.c
index f4725b1d0b..80460ab5d3 100644
--- a/lib/librte_distributor/rte_distributor_single.c
+++ b/lib/librte_distributor/rte_distributor_single.c
@@ -34,8 +34,11 @@ rte_distributor_request_pkt_single(struct rte_distributor_single *d,
 	int64_t req = (((int64_t)(uintptr_t)oldpkt) << RTE_DISTRIB_FLAG_BITS)
 			| RTE_DISTRIB_GET_BUF;
 	while (unlikely(__atomic_load_n(&buf->bufptr64, __ATOMIC_RELAXED)
-			& RTE_DISTRIB_FLAGS_MASK))
+			& RTE_DISTRIB_FLAGS_MASK)) {
 		rte_pause();
+		/* this was an empty poll */
+		RTE_LCORE_TELEMETRY_TIMESTAMP(0);
+	}
 
 	/* Sync with distributor on GET_BUF flag. */
 	__atomic_store_n(&(buf->bufptr64), req, __ATOMIC_RELEASE);
@@ -62,8 +65,11 @@ rte_distributor_get_pkt_single(struct rte_distributor_single *d,
 {
 	struct rte_mbuf *ret;
 	rte_distributor_request_pkt_single(d, worker_id, oldpkt);
-	while ((ret = rte_distributor_poll_pkt_single(d, worker_id)) == NULL)
+	while ((ret = rte_distributor_poll_pkt_single(d, worker_id)) == NULL) {
 		rte_pause();
+		/* this was an empty poll */
+		RTE_LCORE_TELEMETRY_TIMESTAMP(0);
+	}
 	return ret;
 }
 
diff --git a/lib/librte_eal/common/eal_common_lcore_telemetry.c b/lib/librte_eal/common/eal_common_lcore_telemetry.c
new file mode 100644
index 0000000000..5e4ea15ff5
--- /dev/null
+++ b/lib/librte_eal/common/eal_common_lcore_telemetry.c
@@ -0,0 +1,274 @@
+/* SPDX-License-Identifier: BSD-3-Clause
+ * Copyright(c) 2010-2014 Intel Corporation
+ */
+
+#include <unistd.h>
+#include <limits.h>
+#include <string.h>
+
+#include <rte_common.h>
+#include <rte_cycles.h>
+#include <rte_errno.h>
+#include <rte_lcore.h>
+
+#ifdef RTE_LCORE_BUSYNESS
+#include <rte_telemetry.h>
+#endif
+
+int __rte_lcore_telemetry_enabled;
+
+#ifdef RTE_LCORE_BUSYNESS
+
+struct lcore_telemetry {
+	int busyness;
+	/**< Calculated busyness (gets set/returned by the API) */
+	int raw_busyness;
+	/**< Calculated busyness times 100. */
+	uint64_t interval_ts;
+	/**< when previous telemetry interval started */
+	uint64_t empty_cycles;
+	/**< empty cycle count since last interval */
+	uint64_t last_poll_ts;
+	/**< last poll timestamp */
+	bool last_empty;
+	/**< if last poll was empty */
+	unsigned int contig_poll_cnt;
+	/**< contiguous (always empty/non empty) poll counter */
+} __rte_cache_aligned;
+static struct lcore_telemetry telemetry_data[RTE_MAX_LCORE];
+
+#define LCORE_BUSYNESS_MAX 100
+#define LCORE_BUSYNESS_NOT_SET -1
+#define LCORE_BUSYNESS_MIN 0
+
+static void lcore_config_init(void)
+{
+	int lcore_id;
+	RTE_LCORE_FOREACH(lcore_id) {
+		struct lcore_telemetry *td = &telemetry_data[lcore_id];
+
+		td->interval_ts = 0;
+		td->last_poll_ts = 0;
+		td->empty_cycles = 0;
+		td->last_empty = true;
+		td->contig_poll_cnt = 0;
+		td->busyness = LCORE_BUSYNESS_NOT_SET;
+		td->raw_busyness = 0;
+	}
+}
+
+int rte_lcore_busyness(unsigned int lcore_id)
+{
+	const uint64_t active_thresh = RTE_LCORE_BUSYNESS_PERIOD * 1000;
+	struct lcore_telemetry *tdata;
+
+	if (lcore_id >= RTE_MAX_LCORE)
+		return -EINVAL;
+	tdata = &telemetry_data[lcore_id];
+
+	/* if the lcore is not active */
+	if (tdata->interval_ts == 0)
+		return LCORE_BUSYNESS_NOT_SET;
+	/* if the core hasn't been active in a while */
+	else if ((rte_rdtsc() - tdata->interval_ts) > active_thresh)
+		return LCORE_BUSYNESS_NOT_SET;
+
+	/* this core is active, report its busyness */
+	return telemetry_data[lcore_id].busyness;
+}
+
+int rte_lcore_busyness_enabled(void)
+{
+	return __rte_lcore_telemetry_enabled;
+}
+
+void rte_lcore_busyness_enabled_set(int enable)
+{
+	__rte_lcore_telemetry_enabled = !!enable;
+
+	if (!enable)
+		lcore_config_init();
+}
+
+static inline int calc_raw_busyness(const struct lcore_telemetry *tdata,
+				    const uint64_t empty, const uint64_t total)
+{
+	/*
+	 * we don't want to use floating point math here, but we want for our
+	 * busyness to react smoothly to sudden changes, while still keeping the
+	 * accuracy and making sure that over time the average follows busyness
+	 * as measured just-in-time. therefore, we will calculate the average
+	 * busyness using integer math, but shift the decimal point two places
+	 * to the right, so that 100.0 becomes 10000. this allows us to report
+	 * integer values (0..100) while still allowing ourselves to follow the
+	 * just-in-time measurements when we calculate our averages.
+	 */
+	const int max_raw_idle = LCORE_BUSYNESS_MAX * 100;
+
+	/*
+	 * at upper end of the busyness scale, going up from 90->100 will take
+	 * longer than going from 10->20 because of the averaging. to address
+	 * this, we invert the scale when doing calculations: that is, we
+	 * effectively calculate average *idle* cycle percentage, not average
+	 * *busy* cycle percentage. this means that the scale is naturally
+	 * biased towards fast scaling up, and slow scaling down.
+	 */
+	const int prev_raw_idle = max_raw_idle - tdata->raw_busyness;
+
+	/* calculate rate of idle cycles, times 100 */
+	const int cur_raw_idle = (int)((empty * max_raw_idle) / total);
+
+	/* smoothen the idleness */
+	const int smoothened_idle = (cur_raw_idle + prev_raw_idle * 4) / 5;
+
+	/* convert idleness back to busyness */
+	return max_raw_idle - smoothened_idle;
+}
+
+void __rte_lcore_telemetry_timestamp(uint16_t nb_rx)
+{
+	const unsigned int lcore_id = rte_lcore_id();
+	uint64_t interval_ts, empty_cycles, cur_tsc, last_poll_ts;
+	struct lcore_telemetry *tdata = &telemetry_data[lcore_id];
+	const bool empty = nb_rx == 0;
+	uint64_t diff_int, diff_last;
+	bool last_empty;
+
+	last_empty = tdata->last_empty;
+
+	/* optimization: don't do anything if status hasn't changed */
+	if (last_empty == empty && tdata->contig_poll_cnt++ < 32)
+		return;
+	/* status changed or we're waiting for too long, reset counter */
+	tdata->contig_poll_cnt = 0;
+
+	cur_tsc = rte_rdtsc();
+
+	interval_ts = tdata->interval_ts;
+	empty_cycles = tdata->empty_cycles;
+	last_poll_ts = tdata->last_poll_ts;
+
+	diff_int = cur_tsc - interval_ts;
+	diff_last = cur_tsc - last_poll_ts;
+
+	/* is this the first time we're here? */
+	if (interval_ts == 0) {
+		tdata->busyness = LCORE_BUSYNESS_MIN;
+		tdata->raw_busyness = 0;
+		tdata->interval_ts = cur_tsc;
+		tdata->empty_cycles = 0;
+		tdata->contig_poll_cnt = 0;
+		goto end;
+	}
+
+	/* update the empty counter if we got an empty poll earlier */
+	if (last_empty)
+		empty_cycles += diff_last;
+
+	/* have we passed the interval? */
+	if (diff_int > RTE_LCORE_BUSYNESS_PERIOD) {
+		int raw_busyness;
+
+		/* get updated busyness value */
+		raw_busyness = calc_raw_busyness(tdata, empty_cycles, diff_int);
+
+		/* set a new interval, reset empty counter */
+		tdata->interval_ts = cur_tsc;
+		tdata->empty_cycles = 0;
+		tdata->raw_busyness = raw_busyness;
+		/* bring busyness back to 0..100 range, biased to round up */
+		tdata->busyness = (raw_busyness + 50) / 100;
+	} else
+		/* we may have updated empty counter */
+		tdata->empty_cycles = empty_cycles;
+
+end:
+	/* update status for next poll */
+	tdata->last_poll_ts = cur_tsc;
+	tdata->last_empty = empty;
+}
+
+static int
+lcore_busyness_enable(const char *cmd __rte_unused,
+		      const char *params __rte_unused,
+		      struct rte_tel_data *d)
+{
+	rte_lcore_busyness_enabled_set(1);
+
+	rte_tel_data_start_dict(d);
+
+	rte_tel_data_add_dict_int(d, "busyness_enabled", 1);
+
+	return 0;
+}
+
+static int
+lcore_busyness_disable(const char *cmd __rte_unused,
+		       const char *params __rte_unused,
+		       struct rte_tel_data *d)
+{
+	rte_lcore_busyness_enabled_set(0);
+
+	rte_tel_data_start_dict(d);
+
+	rte_tel_data_add_dict_int(d, "busyness_enabled", 0);
+
+	return 0;
+}
+
+static int
+lcore_handle_busyness(const char *cmd __rte_unused,
+		      const char *params __rte_unused, struct rte_tel_data *d)
+{
+	char corenum[64];
+	int i;
+
+	rte_tel_data_start_dict(d);
+
+	RTE_LCORE_FOREACH(i) {
+		if (!rte_lcore_is_enabled(i))
+			continue;
+		snprintf(corenum, sizeof(corenum), "%d", i);
+		rte_tel_data_add_dict_int(d, corenum, rte_lcore_busyness(i));
+	}
+
+	return 0;
+}
+
+RTE_INIT(lcore_init_telemetry)
+{
+	__rte_lcore_telemetry_enabled = true;
+
+	lcore_config_init();
+
+	rte_telemetry_register_cmd("/eal/lcore/busyness", lcore_handle_busyness,
+				   "return percentage busyness of cores");
+
+	rte_telemetry_register_cmd("/eal/lcore/busyness_enable", lcore_busyness_enable,
+				   "enable lcore busyness measurement");
+
+	rte_telemetry_register_cmd("/eal/lcore/busyness_disable", lcore_busyness_disable,
+				   "disable lcore busyness measurement");
+}
+
+#else
+
+int rte_lcore_busyness(unsigned int lcore_id __rte_unused)
+{
+	return -ENOTSUP;
+}
+
+int rte_lcore_busyness_enabled(void)
+{
+	return -ENOTSUP;
+}
+
+void rte_lcore_busyness_enabled_set(int enable __rte_unused)
+{
+}
+
+void __rte_lcore_telemetry_timestamp(uint16_t nb_rx __rte_unused)
+{
+}
+
+#endif
diff --git a/lib/librte_eal/common/meson.build b/lib/librte_eal/common/meson.build
index 39abf7a0a4..8a9668a137 100644
--- a/lib/librte_eal/common/meson.build
+++ b/lib/librte_eal/common/meson.build
@@ -18,6 +18,7 @@ if is_windows
 		'eal_common_fbarray.c',
 		'eal_common_hexdump.c',
 		'eal_common_launch.c',
+		'eal_common_lcore_telemetry.c',
 		'eal_common_lcore.c',
 		'eal_common_log.c',
 		'eal_common_mcfg.c',
@@ -51,6 +52,7 @@ sources += files(
 	'eal_common_hexdump.c',
 	'eal_common_hypervisor.c',
 	'eal_common_launch.c',
+	'eal_common_lcore_telemetry.c',
 	'eal_common_lcore.c',
 	'eal_common_log.c',
 	'eal_common_mcfg.c',
diff --git a/lib/librte_eal/include/rte_lcore.h b/lib/librte_eal/include/rte_lcore.h
index 48b87e253a..c49669f271 100644
--- a/lib/librte_eal/include/rte_lcore.h
+++ b/lib/librte_eal/include/rte_lcore.h
@@ -460,6 +460,86 @@ rte_ctrl_thread_create(pthread_t *thread, const char *name,
 		const pthread_attr_t *attr,
 		void *(*start_routine)(void *), void *arg);
 
+/**
+ * @warning
+ * @b EXPERIMENTAL: this API may change without prior notice.
+ *
+ * Read busyness value corresponding to an lcore.
+ *
+ * @param lcore_id
+ *   Lcore to read busyness value for.
+ * @return
+ *   - value between 0 and 100 on success
+ *   - -1 if lcore is not active
+ *   - -EINVAL if lcore is invalid
+ *   - -ENOMEM if not enough memory available
+ *   - -ENOTSUP if not supported
+ */
+__rte_experimental
+int
+rte_lcore_busyness(unsigned int lcore_id);
+
+/**
+ * @warning
+ * @b EXPERIMENTAL: this API may change without prior notice.
+ *
+ * Check if lcore busyness telemetry is enabled.
+ *
+ * @return
+ *   - 1 if lcore telemetry is enabled
+ *   - 0 if lcore telemetry is disabled
+ *   - -ENOTSUP if not lcore telemetry supported
+ */
+__rte_experimental
+int
+rte_lcore_busyness_enabled(void);
+
+/**
+ * @warning
+ * @b EXPERIMENTAL: this API may change without prior notice.
+ *
+ * Enable or disable busyness telemetry.
+ *
+ * @param enable
+ *   1 to enable, 0 to disable
+ */
+__rte_experimental
+void
+rte_lcore_busyness_enabled_set(int enable);
+
+/**
+ * @warning
+ * @b EXPERIMENTAL: this API may change without prior notice.
+ *
+ * Lcore telemetry timestamping function.
+ *
+ * @param nb_rx
+ *   Number of buffers processed by lcore.
+ */
+__rte_experimental
+void
+__rte_lcore_telemetry_timestamp(uint16_t nb_rx);
+
+/** @internal lcore telemetry enabled status */
+extern int __rte_lcore_telemetry_enabled;
+
+/**
+ * Call lcore telemetry timestamp function.
+ *
+ * @param nb_rx
+ *   Number of buffers processed by lcore.
+ */
+#ifdef RTE_LCORE_BUSYNESS
+#define RTE_LCORE_TELEMETRY_TIMESTAMP(nb_rx)                    \
+	do {                                                    \
+		if (__rte_lcore_telemetry_enabled)              \
+			__rte_lcore_telemetry_timestamp(nb_rx); \
+	} while (0)
+#else
+#define RTE_LCORE_TELEMETRY_TIMESTAMP(nb_rx) \
+	while (0) {}
+#endif
+
 #ifdef __cplusplus
 }
 #endif
diff --git a/lib/librte_eal/meson.build b/lib/librte_eal/meson.build
index 7d6222e781..9198625c83 100644
--- a/lib/librte_eal/meson.build
+++ b/lib/librte_eal/meson.build
@@ -18,6 +18,9 @@ subdir(arch_subdir)
 deps += ['kvargs']
 if not is_windows
 	deps += ['telemetry']
+else
+	# core busyness telemetry depends on telemetry library
+	dpdk_conf.set('RTE_LCORE_BUSYNESS', 0)
 endif
 if dpdk_conf.has('RTE_USE_LIBBSD')
 	ext_deps += libbsd
diff --git a/lib/librte_eal/version.map b/lib/librte_eal/version.map
index 354c068f31..3bf60dbafb 100644
--- a/lib/librte_eal/version.map
+++ b/lib/librte_eal/version.map
@@ -403,6 +403,13 @@ EXPERIMENTAL {
 	rte_service_lcore_may_be_active;
 	rte_vect_get_max_simd_bitwidth;
 	rte_vect_set_max_simd_bitwidth;
+
+	__rte_lcore_telemetry_timestamp;
+	__rte_lcore_telemetry_enabled;
+	rte_lcore_busyness;
+	rte_lcore_busyness_enabled;
+	rte_lcore_busyness_enabled_set;
+
 };
 
 INTERNAL {
diff --git a/lib/librte_ethdev/rte_ethdev.h b/lib/librte_ethdev/rte_ethdev.h
index f5f8919186..a81c3cd27b 100644
--- a/lib/librte_ethdev/rte_ethdev.h
+++ b/lib/librte_ethdev/rte_ethdev.h
@@ -4871,6 +4871,8 @@ rte_eth_rx_burst(uint16_t port_id, uint16_t queue_id,
 #endif
 
 	rte_ethdev_trace_rx_burst(port_id, queue_id, (void **)rx_pkts, nb_rx);
+
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_rx);
 	return nb_rx;
 }
 
diff --git a/lib/librte_eventdev/rte_eventdev.h b/lib/librte_eventdev/rte_eventdev.h
index ce1fc2ce0f..820b3ba73d 100644
--- a/lib/librte_eventdev/rte_eventdev.h
+++ b/lib/librte_eventdev/rte_eventdev.h
@@ -1663,13 +1663,19 @@ rte_event_dequeue_burst(uint8_t dev_id, uint8_t port_id, struct rte_event ev[],
 	 * Allow zero cost non burst mode routine invocation if application
 	 * requests nb_events as const one
 	 */
-	if (nb_events == 1)
-		return (*dev->dequeue)(
-			dev->data->ports[port_id], ev, timeout_ticks);
-	else
-		return (*dev->dequeue_burst)(
-			dev->data->ports[port_id], ev, nb_events,
-				timeout_ticks);
+	if (nb_events == 1) {
+		const uint16_t nb_evts =
+				(*dev->dequeue)(dev->data->ports[port_id],
+					ev, timeout_ticks);
+		RTE_LCORE_TELEMETRY_TIMESTAMP(nb_evts);
+		return nb_evts;
+	} else {
+		const uint16_t nb_evts =
+				(*dev->dequeue_burst)(dev->data->ports[port_id],
+					ev, nb_events, timeout_ticks);
+		RTE_LCORE_TELEMETRY_TIMESTAMP(nb_evts);
+		return nb_evts;
+	}
 }
 
 /**
diff --git a/lib/librte_rawdev/rte_rawdev.c b/lib/librte_rawdev/rte_rawdev.c
index f29164dd15..c37712a3f0 100644
--- a/lib/librte_rawdev/rte_rawdev.c
+++ b/lib/librte_rawdev/rte_rawdev.c
@@ -240,12 +240,15 @@ rte_rawdev_dequeue_buffers(uint16_t dev_id,
 			   rte_rawdev_obj_t context)
 {
 	struct rte_rawdev *dev;
+	int nb_ops;
 
 	RTE_RAWDEV_VALID_DEVID_OR_ERR_RET(dev_id, -EINVAL);
 	dev = &rte_rawdevs[dev_id];
 
 	RTE_FUNC_PTR_OR_ERR_RET(*dev->dev_ops->dequeue_bufs, -ENOTSUP);
-	return (*dev->dev_ops->dequeue_bufs)(dev, buffers, count, context);
+	nb_ops = (*dev->dev_ops->dequeue_bufs)(dev, buffers, count, context);
+	RTE_LCORE_TELEMETRY_TIMESTAMP(nb_ops);
+	return nb_ops;
 }
 
 int
diff --git a/lib/librte_regexdev/rte_regexdev.h b/lib/librte_regexdev/rte_regexdev.h
index 0001658925..b3ec648ca9 100644
--- a/lib/librte_regexdev/rte_regexdev.h
+++ b/lib/librte_regexdev/rte_regexdev.h
@@ -1524,6 +1524,7 @@ rte_regexdev_dequeue_burst(uint8_t dev_id, uint16_t qp_id,
 			   struct rte_regex_ops **ops, uint16_t nb_ops)
 {
 	struct rte_regexdev *dev = &rte_regex_devices[dev_id];
+	uint16_t deq_ops;
 #ifdef RTE_LIBRTE_REGEXDEV_DEBUG
 	RTE_REGEXDEV_VALID_DEV_ID_OR_ERR_RET(dev_id, -EINVAL);
 	RTE_FUNC_PTR_OR_ERR_RET(*dev->dequeue, -ENOTSUP);
@@ -1532,7 +1533,9 @@ rte_regexdev_dequeue_burst(uint8_t dev_id, uint16_t qp_id,
 		return -EINVAL;
 	}
 #endif
-	return (*dev->dequeue)(dev, qp_id, ops, nb_ops);
+	deq_ops = (*dev->dequeue)(dev, qp_id, ops, nb_ops);
+	RTE_LCORE_TELEMETRY_TIMESTAMP(deq_ops);
+	return deq_ops;
 }
 
 #ifdef __cplusplus
diff --git a/lib/librte_ring/rte_ring_elem.h b/lib/librte_ring/rte_ring_elem.h
index 7034d29c07..341bdf8dec 100644
--- a/lib/librte_ring/rte_ring_elem.h
+++ b/lib/librte_ring/rte_ring_elem.h
@@ -475,6 +475,8 @@ __rte_ring_do_dequeue_elem(struct rte_ring *r, void *obj_table,
 end:
 	if (available != NULL)
 		*available = entries - n;
+
+	RTE_LCORE_TELEMETRY_TIMESTAMP(n);
 	return n;
 }
 

From patchwork Fri Jul 15 13:12:54 2022
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Burakov, Anatoly" <anatoly.burakov@intel.com>
X-Patchwork-Id: 113985
X-Patchwork-Delegate: thomas@monjalon.net
Return-Path: <dev-bounces@dpdk.org>
X-Original-To: patchwork@inbox.dpdk.org
Delivered-To: patchwork@inbox.dpdk.org
Received: from mails.dpdk.org (mails.dpdk.org [217.70.189.124])
	by inbox.dpdk.org (Postfix) with ESMTP id 9431DA0032;
	Fri, 15 Jul 2022 15:13:24 +0200 (CEST)
Received: from [217.70.189.124] (localhost [127.0.0.1])
	by mails.dpdk.org (Postfix) with ESMTP id 583FF40696;
	Fri, 15 Jul 2022 15:13:22 +0200 (CEST)
Received: from mga06.intel.com (mga06b.intel.com [134.134.136.31])
 by mails.dpdk.org (Postfix) with ESMTP id CBF7240696
 for <dev@dpdk.org>; Fri, 15 Jul 2022 15:13:18 +0200 (CEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
 d=intel.com; i=@intel.com; q=dns/txt; s=Intel;
 t=1657890799; x=1689426799;
 h=from:to:subject:date:message-id:in-reply-to:references:
 mime-version:content-transfer-encoding;
 bh=h77i2d7CtD3Vs/vdrLhOOL0sTuGrEcf8SUYINxmxwlE=;
 b=NF3a5QAwfg3BGYnzh9nf0+jP5cIRQZPlTFZ+hlbCPH+Gr7ZRe5xQ/go5
 vm9AYdDZsWhD7+a1IHDRq3MXpxkrtL9vI3kqtJd66sgXR8iPLayhSlBRg
 DvM2hepv/1Fp6G1Kc6fqBtVTz2h70VCULpS68nYQA+e4dcANDsTwm8KpS
 i6mpJM+9yDGNrMksuVbIjuvpRFs5CQG0kkZqx6k6mAuta+o3AhkpXkGAJ
 Ze4k7ArfS7/4TZxakp7nNuadzbcMTH1iJ9UzPyLorovq6JQAt6GT89HTM
 NzJmQV4VBDj/kMA0Vb0n6T9C3cJyoIsEW9VmIUM1r6/4QoUeuTYNXq+1J A==;
X-IronPort-AV: E=McAfee;i="6400,9594,10408"; a="347467266"
X-IronPort-AV: E=Sophos;i="5.92,274,1650956400"; d="scan'208";a="347467266"
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
 by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2022 06:13:00 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.92,274,1650956400"; d="scan'208";a="685956357"
Received: from silpixa00401191.ir.intel.com ([10.55.128.75])
 by FMSMGA003.fm.intel.com with ESMTP; 15 Jul 2022 06:13:00 -0700
From: Anatoly Burakov <anatoly.burakov@intel.com>
To: dev@dpdk.org
Subject: [20.11 PATCH v1 2/2] eal: add cpuset lcore telemetry entries
Date: Fri, 15 Jul 2022 13:12:54 +0000
Message-Id: 
 <3f66bf233f9f1ef28c93ca22fa0972491b36c3e8.1657890738.git.anatoly.burakov@intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: 
 <eab9994ef9e9531e6ed03773a1ecd2654a196a3d.1657890738.git.anatoly.burakov@intel.com>
References: 
 <eab9994ef9e9531e6ed03773a1ecd2654a196a3d.1657890738.git.anatoly.burakov@intel.com>
MIME-Version: 1.0
X-BeenThere: dev@dpdk.org
X-Mailman-Version: 2.1.29
Precedence: list
List-Id: DPDK patches and discussions <dev.dpdk.org>
List-Unsubscribe: <https://mails.dpdk.org/options/dev>,
 <mailto:dev-request@dpdk.org?subject=unsubscribe>
List-Archive: <http://mails.dpdk.org/archives/dev/>
List-Post: <mailto:dev@dpdk.org>
List-Help: <mailto:dev-request@dpdk.org?subject=help>
List-Subscribe: <https://mails.dpdk.org/listinfo/dev>,
 <mailto:dev-request@dpdk.org?subject=subscribe>
Errors-To: dev-bounces@dpdk.org

Expose per-lcore cpuset information to telemetry.

Signed-off-by: Anatoly Burakov <anatoly.burakov@intel.com>
---
 .../common/eal_common_lcore_telemetry.c       | 47 +++++++++++++++++++
 1 file changed, 47 insertions(+)

diff --git a/lib/librte_eal/common/eal_common_lcore_telemetry.c b/lib/librte_eal/common/eal_common_lcore_telemetry.c
index 5e4ea15ff5..39fffe2b93 100644
--- a/lib/librte_eal/common/eal_common_lcore_telemetry.c
+++ b/lib/librte_eal/common/eal_common_lcore_telemetry.c
@@ -19,6 +19,8 @@ int __rte_lcore_telemetry_enabled;
 
 #ifdef RTE_LCORE_BUSYNESS
 
+#include "eal_private.h"
+
 struct lcore_telemetry {
 	int busyness;
 	/**< Calculated busyness (gets set/returned by the API) */
@@ -235,6 +237,48 @@ lcore_handle_busyness(const char *cmd __rte_unused,
 	return 0;
 }
 
+static int
+lcore_handle_cpuset(const char *cmd __rte_unused,
+		    const char *params __rte_unused,
+		    struct rte_tel_data *d)
+{
+	char corenum[64];
+	int i;
+
+	rte_tel_data_start_dict(d);
+
+	RTE_LCORE_FOREACH(i) {
+		const struct lcore_config *cfg = &lcore_config[i];
+		const rte_cpuset_t *cpuset = &cfg->cpuset;
+		struct rte_tel_data *ld;
+		unsigned int cpu;
+
+		if (!rte_lcore_is_enabled(i))
+			continue;
+
+		/* create an array of integers */
+		ld = rte_tel_data_alloc();
+		if (ld == NULL)
+			return -ENOMEM;
+		rte_tel_data_start_array(ld, RTE_TEL_INT_VAL);
+
+		/* add cpu ID's from cpuset to the array */
+		for (cpu = 0; cpu < CPU_SETSIZE; cpu++) {
+			if (!CPU_ISSET(cpu, cpuset))
+				continue;
+			rte_tel_data_add_array_int(ld, cpu);
+		}
+
+		/* add array to the per-lcore container */
+		snprintf(corenum, sizeof(corenum), "%d", i);
+
+		/* tell telemetry library to free this array automatically */
+		rte_tel_data_add_dict_container(d, corenum, ld, 0);
+	}
+
+	return 0;
+}
+
 RTE_INIT(lcore_init_telemetry)
 {
 	__rte_lcore_telemetry_enabled = true;
@@ -249,6 +293,9 @@ RTE_INIT(lcore_init_telemetry)
 
 	rte_telemetry_register_cmd("/eal/lcore/busyness_disable", lcore_busyness_disable,
 				   "disable lcore busyness measurement");
+
+	rte_telemetry_register_cmd("/eal/lcore/cpuset", lcore_handle_cpuset,
+				   "list physical core affinity for each lcore");
 }
 
 #else
