# LoRaTap
LoRaTap encapsulation

Encapsulation format to be used to store LoRa traffic in pcap files.
	
Field details (Values are big-endian)
* `lt_version`, LoRaTap header version, current version is 0.
* `lt_padding`, Unused, for boundary alignment.
* `lt_length`, LoRaTap header length, field used to allow expansion in future versions. Each version can append header parameters. So, whilst parsing, these parameters can be skipped if not defined for older versions by skipping to the offset of lt_length starting from the beginning of the header.
* `packet_rssi`, RSSI of last packet (dBm)
* `rssi`, Current RSSI (dBm)
* `snr`, Estimation of last packet SNR (dB)
* `sf`, The spreading factor as used for the radio packet
* `frequency`, Frequency packet was received on (MHz)

```
typedef struct loratap_header {
	uint8_t				lt_version;	/* LoRatap header version */
	uint8_t				lt_padding;
	uint16_t			lt_length;	/* LoRatap header length */
	uint8_t				packet_rssi;	/* LoRa packet RSSI (dBm) */
	uint8_t				rssi;		/* LoRa receiver RSSI (dBm) */
	uint8_t				snr;		/* LoRa SNR (dB) */
	uint8_t				sf;		/* LoRa SF [sf_t] */
	uint32_t			frequency;	/* LoRa frequency (MHz) */
} loratap_header_t __attribute__ ((packed));
```
