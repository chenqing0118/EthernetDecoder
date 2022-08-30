// simig_decoder.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include <string>
#include "simig_struct.h"
namespace simig {
	namespace decoder {
		double decode_lat_lon_40(int msw,int lsw);
		inline double decodeInt2Double(int inNum,double scale) {
			return (double)inNum * scale;
		}
		char char2int(char ch);
		char merge_char(char ch1, char ch2);
		int  merge_int(char ch1, char ch2, char ch3, char ch4);
		void process(std::string raw_file);
		void process_only_21(std::string raw_file);
		void process_only_82(std::string raw_file);
		void process_only_86(std::string raw_file);
	}
}
