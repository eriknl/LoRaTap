# LoRaTap
LoRaTap encapsulation

Encapsulation format to be used to store LoRa traffic in pcap files.

```
typedef struct loratap_header {
	uint16_t			lt_version;	/* LoRatap header version */
	uint16_t			lt_len;		/* LoRatap header length */
	uint8_t				packet_rssi;	/* LoRa packet RSSI */
	uint8_t				rssi;		/* LoRa receiver RSSI */
	uint8_t				snr;		/* LoRa SNR */
	uint8_t				_padding;
	uint32_t			frequency;	/* LoRa frequency */
	uint8_t				sf;		/* LoRa SF */
	uint16_t			length;		/* LoRa packet length */
	uint8_t				_padding2;
} loratap_header_t;
```
