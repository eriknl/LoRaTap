# LoRaTap

Encapsulation format to be used to store LoRa traffic in pcap files.
	
### LoRaTap encapsulation, version 0

Field details defined in [loratap.h](loratap.h) (Values are big-endian)

* `lt_version`, LoRaTap header version, current version is 0.
* `lt_padding`, Unused, for boundary alignment.
* `lt_length`, LoRaTap header length, field used to allow expansion in future versions. Each version can append header parameters. So, whilst parsing, these parameters can be skipped if not defined for older versions by skipping to the offset of lt_length starting from the beginning of the header.
* `channel`, Channel information
* `rssi`, RSSI information
* `sync_word`, Sync word for received packet, value 0x34 is reserved for LoRaWAN packets

```
typedef enum sf { SF7=7, SF8, SF9, SF10, SF11, SF12 } sf_t;

typedef struct  __attribute__((__packed__)) loratap_channel {
	uint32_t			frequency;	/* LoRa frequency (Hz) */
	uint8_t				bandwidth;	/* Channel bandwidth (KHz) in 125 KHz steps */
	uint8_t				sf;		/* LoRa SF (sf_t) [7, 8, 9, 10, 11, 12] */
} loratap_channel_t;

typedef struct  __attribute__((__packed__)) loratap_rssi {
	uint8_t				packet_rssi;	/* LoRa packet RSSI, if snr >= 0 then dBm value is -139 + packet_rssi, otherwise dBm value is -139 + packet_rssi * .25 */
	uint8_t				max_rssi;	/* LoRa receiver max RSSI (dBm value is -139 + rssi) */
	uint8_t				current_rssi;	/* LoRa receiver current RSSI (dBm value is -139 + rssi) */
	uint8_t				snr;		/* LoRa SNR (dB value is (snr[two's complement])/4) */
} loratap_rssi_t;

typedef struct  __attribute__((__packed__)) loratap_header {
	uint8_t				lt_version;	/* LoRatap header version */
	uint8_t				lt_padding;
	uint16_t			lt_length;	/* LoRatap header length */
	loratap_channel_t		channel;
	loratap_rssi_t			rssi;
	uint8_t				sync_word;	/* LoRa radio sync word [0x34 = LoRaWAN] */
} loratap_header_t;
```

### LoRaTap encapsulation, version 1

New version extends original header to support fields used by [Semtech Packet Forwarder](https://github.com/Lora-net/packet_forwarder).

Field details defined in [loratap1.h](loratap1.h) (Values are big-endian)
* `lt_version`, LoRaTap header version, current version is 1.
* `lt_padding`, Unused, for boundary alignment.
* `lt_length`, LoRaTap header length, field used to allow expansion in future versions. Each version can append header parameters. So, whilst parsing, these parameters can be skipped if not defined for older versions by skipping to the offset of lt_length starting from the beginning of the header.
* `channel`, Channel information. RSSI value 255 stands for N/A.
* `rssi`, RSSI information.
* `sync_word`, Sync word for received packet, value 0x34 is reserved for LoRaWAN packets.
* `source_gw`, Source gateway ID.
* `timestamp`, Internal timestamp.
* `flags`, Packet flags (see loratap_flags_t).
* `cr`, LoRa coding rate.
* `datarate`, FSK datarate.
* `if_channel`, Concentrator "IF" channel used for RX.
* `rf_chain`, Concentrator "RF chain" used for RX.
* `tag`, Packet tag, extended information for future use (LoRaWAN simulator source, gateway packet marker etc.).

```
typedef enum sf { SF5=5, SF6, SF7, SF8, SF9, SF10, SF11, SF12 } sf_t;

typedef enum cr { CR_NONE=0, CR_4_5=5, CR_4_6=6, CR_4_7=7, CR_4_8=8 } cr_t;

/* loratap_channel_t unchanged */

/* loratap_rssi_t unchanged */

typedef struct __attribute__((__packed__)) loratap_flags {
	uint8_t				mod_fsk:1;	/* FSK (1) or LoRa (0) modulation */
	uint8_t				iq_inverted:1;	/* LoRa chirp polarization (uplink non-inverted, downlink inverted) */
	uint8_t				implicit_hdr:1;	/* LoRa implicit header mode (Class-B beacon) */
	uint8_t				crc_ok:1;	/* Packet CRC valid */
	uint8_t				crc_bad:1;	/* Packet CRC invalid */
	uint8_t				no_crc:1;	/* Packet without CRC */
	uint8_t				padding:2;	/* Padding (RFU) */
} loratap_flags_t;

typedef struct __attribute__((__packed__)) loratap_header {
	/* Version 0, unchanged */
	uint8_t				lt_version;	/* LoRatap header version */
	uint8_t				lt_padding;
	uint16_t			lt_length;	/* LoRatap header length */
	loratap_channel_t		channel;
	loratap_rssi_t			rssi;
	uint8_t				sync_word;	/* LoRa radio sync word [0x34 = LoRaWAN] */
	/* Version 1 */
	uint64_t			source_gw;	/* Source gateway ID */
	uint32_t			timestamp;	/* Internal timestamp of SX1301 "RX finished" event (tmst) */
	loratap_flags_t			flags;		/* Packet flags */
	uint8_t				cr;		/* LoRa coding rate (cr_t) [0, 5, 6, 7, 8] */
	uint16_t			datarate;	/* FSK datarate (bits per second) */
	uint8_t				if_channel;	/* Concentrator "IF" channel used for RX (chan) */
	uint8_t				rf_chain;	/* Concentrator "RF chain" used for RX (rfch) */
	uint16_t			tag;		/* Packet tag */
} loratap_header_t;
```
