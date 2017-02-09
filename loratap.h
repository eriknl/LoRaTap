/*
This file is part of LoRaTap Copyright (C) 2017 Erik de Jong

LoRaTap is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

LoRaTap is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LoRaTap.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>

/*
	Values are big-endian
	
	Field details
	lt_version	LoRaTap header version, current version is 0.
	lt_padding	Unused, for boundary alignment.
	lt_length	LoRaTap header length, field used to allow expansion in future versions. Each version can append header parameters. 
			So, whilst parsing, these parameters can be skipped if not defined for older versions by skipping to the offset of lt_length starting from the beginning of the header.
	packet_rssi	RSSI of last packet (dBm)
	rssi		Current RSSI (dBm)
	snr		Espimation of last packet SNR (dB)
	sf		The spreading factor as used for the radio packet
	frequency	Frequency packet was received on (MHz)
*/

typedef enum sf { SF7=7, SF8, SF9, SF10, SF11, SF12 } sf_t;

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
