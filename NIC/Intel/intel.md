
The following case will case Tx hang

Scenario: large packet than max fame(9728 bytes)


Scenario：small packet less than 17 bytes


Scenario of fragment：first pkt nb_seg value doesn’t equal real chain segment number


Scenario of fragment：datalen of any pkt segment in the chain is set as 0


Scenario of fragment: pktlen is different (wrong) with each data_len(not hang, just wrong statistics)


Seenario of fragment: number of the segment is more than 8 for x7xx, more than 40 for x5xx


DD位（Descriptor Done Status）用于标志标识一个描述符buf是否可用。

网卡每次来了新的数据包，就检查rx_ring当前这个buf的DD位是否为0，如果为0那么表示当前buf可以使用，就让DMA将数据包copy到这个buf中，然后设置DD为1。如果为1，那么网卡就认为rx_ring队列满了，直接会将这个包给丢弃掉，记录一次imiss。（0->1）

对于应用而言，DD位使用恰恰相反，在读取数据包时，先检查DD位是否为1，如果为1，表示网卡已经把数据包放到了内存中，可以读取，读取完后，再放入一个新的buf并把对应DD位设置为0。如果为0，就表示没有数据包可读。（1->0）

