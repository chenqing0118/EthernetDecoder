// simig_decoder.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include "configor/json.hpp"
#include "simig_struct.h"
namespace simig {
	namespace command_json {
		void gen_json_21(command_struct::packet_21* pk_21, configor::json& out_json);
		void gen_json_40(command_struct::packet_40* pk_40, configor::json& out_json);
		void gen_json_42(command_struct::packet_42* pk_42, configor::json& out_json);
		void gen_json_43(command_struct::packet_43* pk_43, configor::json& out_json);
		void gen_json_44(command_struct::packet_44* pk_44, configor::json& out_json);
		void gen_json_45(command_struct::packet_45* pk_45, configor::json& out_json);
		void gen_json_47(command_struct::packet_47* pk_47, configor::json& out_json);
		void gen_json_52(command_struct::packet_52* pk_52, configor::json& out_json);
		void gen_json_55(command_struct::packet_55* pk_55, configor::json& out_json);

		void gen_json_82(command_struct::fb_packet_82* pk_fb_82, configor::json& out_json);
		void gen_json_86(command_struct::fb_packet_86* pk_fb_86, configor::json& out_json);
	}
}


// TODO: 在此处引用程序需要的其他标头。
