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

typedef struct loratap_header {
	uint16_t			lt_version;	/* LoRatap header version */
	uint16_t			lt_len;		/* LoRatap header length */
	uint8_t				packet_rssi;	/* LoRa packet RSSI */
	uint8_t				rssi;		/* LoRa receiver RSSI */
	uint8_t				snr;		/* LoRa SNR */
	uint8_t				_padding;
	uint32_t			frequency;	/* LoRa frequency */
	uint8_t				sf;		/* LoRa SF */
	uint8_t				_padding2;
	uint16_t			length;		/* LoRa packet length */
} loratap_header_t;
