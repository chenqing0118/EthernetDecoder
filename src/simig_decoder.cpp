// simig_decoder.cpp: 定义应用程序的入口点。
//
#include "simig_decoder.h"

#include "simig_gen_json.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
double simig::decoder:: decode_lat_lon_40(int msw, int lsw)
{
	static double
		lat_lon
		, dscratch
		, dscratch1
		, dscratch2
		, dscratch3
		;
	dscratch = (double)msw;
	dscratch1 = dscratch * POW2_32;
	dscratch2 = (double)lsw;
	if (dscratch2 < 0) dscratch2 += POW2_32;
	dscratch3 = dscratch1 + dscratch2;
	lat_lon = dscratch3 * REV2_DEG;
	return lat_lon;
}
std::string DecodeUIntToICAO( int icao) {
	char* icao_str=new char[4];
	icao_str[0] = (icao & 0x000000ff);
	icao_str[1] = ((icao >> 8) & 0x000000ff);
	icao_str[2] = ((icao >> 16) & 0x000000ff);
	icao_str[3] = ((icao >> 24) & 0x000000ff);
	std::string outstr = icao_str;//这是深拷贝。
	delete []icao_str;
	return outstr;
	
}
char simig::decoder::char2int(char ch) {
	if (ch <= '9')
	{
		return ch - '0';
	}
	else {
		return ch - 'a' + 10;
	}
}
char simig::decoder::merge_char(char ch1, char ch2) {
	char result = 0;
	result += char2int(ch1);
	result <<= 4;
	result += char2int(ch2);
	return result;
}
int simig::decoder::merge_int(char ch1, char ch2, char ch3, char ch4) {
	int result = 0;
	result += ch1;
	result <<= 4;
	result += ch2;
	result <<= 4;
	result += ch3;
	result <<= 4;
	result += ch4;
	return result;
}
void simig::decoder::process(std::string raw_file) {
	using namespace std;
	string s;
	ifstream inf;
	inf.open(raw_file+"test.txt");
	fstream of1;
	of1.open(raw_file+"21h.txt", ios::out | ios::app);
	fstream of2;
	of2.open(raw_file+"86h.txt", ios::out | ios::app);
	static int line = 0;
	vector<unsigned char> frame_content;
	frame_content.resize(1500);

	vector<configor::json> commands;
	static int fback_index = 0;
	int pa21 = 0, pa86 = 0;
	while (getline(inf, s))
	{
		using namespace simig;
		static configor::json buffer;

		++line;
		//获取时间戳
		if (line == 2) {
			regex ex("\\d{2}:\\d{2}:\\d{2},\\d{3},\\d{3}");
			smatch match;
			regex_search(s, match, ex);
			buffer["timestamp"] = match[0];
		}
		//获取命令内容，可能含有多条命令
		if (line == 3) {
			//cout << s << endl;
			configor::json command;
			regex ex("\\w{2}");
			auto iter_begin = sregex_iterator(s.begin(), s.end(), ex);
			auto iter_end = sregex_iterator();
			int char_index = 0;
			//将16进制内容存为字符数组
			for (auto iter = iter_begin; iter != iter_end; ++iter, ++char_index)
			{
				string temp = iter->str();
				char hex = decoder::merge_char(temp[0], temp[1]);
				frame_content[char_index] = hex;
			}
			//获取ethernet header
			static command_struct::Eth_Header* eth_header = (command_struct::Eth_Header*)(&frame_content[fback_index]);
			//cout <<hex<< int(eth_header->des_mac.mac1) << '\t' << int(eth_header->source_mac.mac1) << '\t' << eth_header->size << endl;
			fback_index += ETH_HEADER_LENGTH;
			//获取cae_header
			static command_struct::CAE_Header* cae_header = (command_struct::CAE_Header*)(&frame_content[fback_index]);
			//cout << dec << cae_header->byte_count.size << endl;
			fback_index += CAE_HEADER_LENGTH;
			//获取 message number
			static command_struct::Massage_Number* message_number = (command_struct::Massage_Number*)(&frame_content[fback_index]);
			//cout << hex << message_number->number << endl;
			buffer["message_number"]=message_number->number;
			fback_index += MESSAGE_NUMBER_LENGTH;
			//获取 visual header
			static command_struct::Visual_Header* visual_header = (command_struct::Visual_Header*)(&frame_content[fback_index]);
			//cout << dec << visual_header->first_word.size << endl;
			int visual_size = visual_header->first_word.size;
			fback_index += VISUAL_HEADER_LENGTH;
			//获取commands内容
			int iter = 0;
			
			if (eth_header->des_mac.mac1 == 0x56) //判断发送源
			{
				buffer["source"] = 1;
				while (iter < visual_size) {
					if (frame_content[fback_index] == 0x86) {
						        static command_struct::fb_packet_86* pk_fb_86;
								pk_fb_86 = (command_struct::fb_packet_86*)(&frame_content[fback_index]);
						        command_json::gen_json_86(pk_fb_86, command);
						        commands.push_back(command);
						        command.clear();
						        iter += (pk_fb_86->header.first_word.size * 4 + 8);
						        fback_index += (pk_fb_86->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x82) {
						        static command_struct::fb_packet_82* pk_fb_82;
								pk_fb_82 = (command_struct::fb_packet_82*)(&frame_content[fback_index]);
						        command_json::gen_json_82(pk_fb_82, command);
						        commands.push_back(command);
						        command.clear();
						        iter += (pk_fb_82->header.first_word.size * 4 + 8);
						        fback_index += (pk_fb_82->header.first_word.size * 4 + 8);
					}
				}
				buffer["commands"] = commands;
				of2 << std::setw(4) << hex << buffer << std::endl;
				cout <<"86h:"<< ++pa86 << endl;
			}
			else if (eth_header->source_mac.mac1 == 0x56) {
				buffer["source"] = 0;
				while (iter < visual_size) {
					if (frame_content[fback_index] == 0x21) {
						        static command_struct::packet_21* pk_21;
								pk_21 = (command_struct::packet_21*)(&frame_content[fback_index]);
						        command_json::gen_json_21(pk_21, command);
						        commands.push_back(command);
						        command.clear();
						        iter += (pk_21->header.first_word.size * 4 + 8);
						        fback_index += (pk_21->header.first_word.size * 4 + 8);
					}
					else if (frame_content[fback_index] == 0x40) {
								static command_struct::packet_40* pk_40;
								pk_40 = (command_struct::packet_40*)(&frame_content[fback_index]);
							    command_json::gen_json_40(pk_40, command);
							    commands.push_back(command);
							    command.clear();
							    iter += (pk_40->header.first_word.size * 4 + 8);
							    fback_index += (pk_40->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x42) {
						        static command_struct::packet_42* pk_42;
								pk_42 = (command_struct::packet_42*)(&frame_content[fback_index]);
								command_json::gen_json_42(pk_42, command);
								commands.push_back(command);
								command.clear();
								iter += (pk_42->header.first_word.size * 4 + 8);
								fback_index += (pk_42->header.first_word.size * 4 + 8);
					}
					else if (frame_content[fback_index] == 0x43) {
						        static command_struct::packet_43* pk_43;
								pk_43 = (command_struct::packet_43*)(&frame_content[fback_index]);
						        command_json::gen_json_43(pk_43, command);
						        commands.push_back(command);
						        command.clear();
						        iter += (pk_43->header.first_word.size * 4 + 8);
						        fback_index += (pk_43->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x44) {
						        static command_struct::packet_44* pk_44;
								pk_44 = (command_struct::packet_44*)(&frame_content[fback_index]);
								command_json::gen_json_44(pk_44, command);
								commands.push_back(command);
								command.clear();
								iter += (pk_44->header.first_word.size * 4 + 8);
								fback_index += (pk_44->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x45) {
						        static command_struct::packet_45* pk_45;
							    pk_45 = (command_struct::packet_45*)(&frame_content[fback_index]);
						        command_json::gen_json_45(pk_45, command);
						        commands.push_back(command);
						        command.clear();
						        iter += (pk_45->header.first_word.size * 4 + 8);
						        fback_index += (pk_45->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x47) {
							    static command_struct::packet_47* pk_47;
								pk_47 = (command_struct::packet_47*)(&frame_content[fback_index]);
							    command_json::gen_json_47(pk_47, command);
							    commands.push_back(command);
							    command.clear();
							    iter += (pk_47->header.first_word.size * 4 + 8);
							    fback_index += (pk_47->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x52) {
								static command_struct::packet_52* pk_52;
								pk_52 = (command_struct::packet_52*)(&frame_content[fback_index]);
								command_json::gen_json_52(pk_52, command);
								commands.push_back(command);
								command.clear();
								iter += (pk_52->header.first_word.size * 4 + 8);
								fback_index += (pk_52->header.first_word.size * 4 + 8);
					}else if (frame_content[fback_index] == 0x55) {
						        static command_struct::packet_55* pk_55;
								pk_55 = (command_struct::packet_55*)(&frame_content[fback_index]);
								command_json::gen_json_55(pk_55, command);
								commands.push_back(command);
								command.clear();
								iter += (pk_55->header.first_word.size * 4 + 8);
								fback_index += (pk_55->header.first_word.size * 4 + 8);
					}
				}
				buffer["commands"] = commands;
				of1 << std::setw(4) << hex << buffer << std::endl;
				cout << "21h:"<<++pa21 << endl;
			}
			else {
				line = 0;
				fback_index = 0;
				commands.clear();
				buffer.clear();
				continue;
			}
		
		}

		if (line == 4) {

			line = 0;
			fback_index = 0;
			commands.clear();
			buffer.clear();
		}
	}
	inf.close();
	of1.close();
	of2.close();
}

void simig::decoder::process_only_21(std::string raw_file) {
	using namespace std;
	string s;
	ifstream inf;
	inf.open(raw_file + "3302zljqws.txt");
	fstream of1;
	of1.open(raw_file + "21h.txt", ios::out | ios::app);
	static int line = 0;
	vector<unsigned char> frame_content;
	frame_content.resize(1500);

	static int fback_index = 0;
	int count= 0;
	string timestamp;
	while (getline(inf, s))
	{
		using namespace simig;

		++line;
		//获取时间戳
		if (line == 2) {
			regex ex("\\d{2}:\\d{2}:\\d{2},\\d{3},\\d{3}");
			smatch match;
			regex_search(s, match, ex);
			timestamp = match[0];
		}
		//获取命令内容，可能含有多条命令
		if (line == 3) {
			//cout << s << endl;

			regex ex("\\w{2}");
			auto iter_begin = sregex_iterator(s.begin(), s.end(), ex);
			auto iter_end = sregex_iterator();
			int char_index = 0;
			//将16进制内容存为字符数组
			for (auto iter = iter_begin; iter != iter_end; ++iter, ++char_index)
			{
				string temp = iter->str();
				char hex = decoder::merge_char(temp[0], temp[1]);
				frame_content[char_index] = hex;
			}
			//获取ethernet header
			static command_struct::Eth_Header* eth_header = (command_struct::Eth_Header*)(&frame_content[fback_index]);
			//cout <<hex<< int(eth_header->des_mac.mac1) << '\t' << int(eth_header->source_mac.mac1) << '\t' << eth_header->size << endl;
			fback_index += ETH_HEADER_LENGTH;
			//获取cae_header
			static command_struct::CAE_Header* cae_header = (command_struct::CAE_Header*)(&frame_content[fback_index]);
			//cout << dec << cae_header->byte_count.size << endl;
			fback_index += CAE_HEADER_LENGTH;
			//获取 message number
			static command_struct::Massage_Number* message_number = (command_struct::Massage_Number*)(&frame_content[fback_index]);
			//buffer["message_number"] = message_number->number;
			//cout << hex << message_number->number << endl;
			fback_index += MESSAGE_NUMBER_LENGTH;
			//获取 visual header
			static command_struct::Visual_Header* visual_header = (command_struct::Visual_Header*)(&frame_content[fback_index]);
			//cout << dec << visual_header->first_word.size << endl;
			int visual_size = visual_header->first_word.size;
			fback_index += VISUAL_HEADER_LENGTH;
			//获取commands内容
			int iter = 0;
			if (eth_header->source_mac.mac1 == 0x56) //判断发送源
			{
				while (iter < visual_size) {
					if (frame_content[fback_index] == 0x21) {

						static command_struct::packet_21* pk_21;
						pk_21 = (command_struct::packet_21*)(&frame_content[fback_index]);
						iter += (pk_21->header.first_word.size * 4 + 8);
						fback_index += (pk_21->header.first_word.size * 4 + 8);
						of1 << timestamp << '\t'
							<< pk_21->header.first_word.opcode<<'\t'
							<< pk_21->header.first_word.channel<<'\t'
							<< pk_21->header.first_word.size<<'\t'
							<< pk_21->header.cs_mask<<'\t'
							<< decoder::decode_lat_lon_40(pk_21->latitude_msw, pk_21->latitude_lsw) << '\t'
							<< decoder::decode_lat_lon_40(pk_21->longitude_msw, pk_21->longitude_lsw) << '\t'
							<< decoder::decodeInt2Double(pk_21->altitude,HMM_M) << '\t'
							<< decoder::decodeInt2Double(pk_21->roll,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->pitch,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->yaw,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->delta_latt,REV2_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->delta_long,REV2_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->delta_alt,HMM_M) << '\t'
							<< decoder::decodeInt2Double(pk_21->delta_roll,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->delta_pitch,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_21->delta_yaw,REV1_DEG) << std::endl;
						++count;
						if (count % 50 == 0)
						{
							std::cout << "21：" << count << std::endl;
						}
					}
					else {
						static command_struct::Command_Header* header;
						header = (command_struct::Command_Header*)(&frame_content[fback_index]);
						iter += (header->first_word.size * 4 + 8);
						fback_index += (header->first_word.size * 4 + 8);
					}
				}	

			}

		}
		if (line == 4) {
			line = 0;
			fback_index = 0;
		}
	}

	inf.close();
	of1.close();
}
void simig::decoder::process_only_82(std::string raw_file) {
	using namespace std;
	string s;
	ifstream inf;
	inf.open(raw_file + "test.txt");
	fstream of1;
	of1.open(raw_file + "82h.txt", ios::out | ios::app);
	static int line = 0;
	vector<unsigned char> frame_content;
	frame_content.resize(1500);

	static int fback_index = 0;
	int count_52 = 0;
	int count_82 = 0;
	string timestamp;
	while (getline(inf, s))
	{
		using namespace simig;

		++line;
		//获取时间戳
		if (line == 2) {
			regex ex("\\d{2}:\\d{2}:\\d{2},\\d{3},\\d{3}");
			smatch match;
			regex_search(s, match, ex);
			timestamp = match[0];
		}
		//获取命令内容，可能含有多条命令
		if (line == 3) {
			//cout << s << endl;
			
			regex ex("\\w{2}");
			auto iter_begin = sregex_iterator(s.begin(), s.end(), ex);
			auto iter_end = sregex_iterator();
			int char_index = 0;
			//将16进制内容存为字符数组
			for (auto iter = iter_begin; iter != iter_end; ++iter, ++char_index)
			{
				string temp = iter->str();
				char hex = decoder::merge_char(temp[0], temp[1]);
				frame_content[char_index] = hex;
			}
			//获取ethernet header
			static command_struct::Eth_Header* eth_header = (command_struct::Eth_Header*)(&frame_content[fback_index]);
			//cout <<hex<< int(eth_header->des_mac.mac1) << '\t' << int(eth_header->source_mac.mac1) << '\t' << eth_header->size << endl;
			fback_index += ETH_HEADER_LENGTH;
			//获取cae_header
			static command_struct::CAE_Header* cae_header = (command_struct::CAE_Header*)(&frame_content[fback_index]);
			//cout << dec << cae_header->byte_count.size << endl;
			fback_index += CAE_HEADER_LENGTH;
			//获取 message number
			static command_struct::Massage_Number* message_number = (command_struct::Massage_Number*)(&frame_content[fback_index]);
			//buffer["message_number"] = message_number->number;
			//cout << hex << message_number->number << endl;
			fback_index += MESSAGE_NUMBER_LENGTH;
			//获取 visual header
			static command_struct::Visual_Header* visual_header = (command_struct::Visual_Header*)(&frame_content[fback_index]);
			//cout << dec << visual_header->first_word.size << endl;
			int visual_size = visual_header->first_word.size;
			fback_index += VISUAL_HEADER_LENGTH;
			//获取commands内容
			int iter = 0;
			if (eth_header->des_mac.mac1 == 0x56) //判断发送源
			{
				while (iter < visual_size) {
					if (frame_content[fback_index] == 0x82) {

						static command_struct::fb_packet_82* pk_fb_82;
						pk_fb_82 = (command_struct::fb_packet_82*)(&frame_content[fback_index]);
						iter += (pk_fb_82->header.first_word.size * 4 + 8);
						fback_index += (pk_fb_82->header.first_word.size * 4 + 8);
						of1 << timestamp<<'\t'
							<< pk_fb_82->header.first_word.opcode<<'\t'
							<< pk_fb_82->header.first_word.channel<<'\t'
							<< pk_fb_82->header.first_word.size<<'\t'
							<< pk_fb_82->header.cs_mask<<'\t'
							<< pk_fb_82->hat_info.id<<'\t'
							<< pk_fb_82->hat_info.channel<<'\t'
							<< pk_fb_82->hat_info.category<<'\t'
							<< pk_fb_82->material<<'\t'
							<< pk_fb_82->equation_Nx / (POW2_31 - 1.0) << '\t'
							<< pk_fb_82->equation_Ny / (POW2_31 - 1.0) << '\t'
							<< pk_fb_82->equation_Nz / (POW2_31 - 1.0) << '\t'
							<< decoder::decodeInt2Double(pk_fb_82->equation_D,HMM_M) <<'\t'
							<< decoder::decodeInt2Double(pk_fb_82->hat,HMM_M) << std::endl;
					}
					else {
						static command_struct::Command_Header* header;
						header = (command_struct::Command_Header*)(&frame_content[fback_index]);
						iter += (header->first_word.size * 4 + 8);
						fback_index += (header->first_word.size * 4 + 8);
					}
				}
				std::cout << "82：" << ++count_82 << std::endl;
				
			}
			
		}
		if (line == 4) {
			line = 0;
			fback_index = 0;
		}
	}

	inf.close();
	of1.close();
}
void simig::decoder::process_only_86(std::string raw_file) {
	using namespace std;
	string s;
	ifstream inf;
	inf.open(raw_file + "3302zljqws.txt");
	fstream of1;
	of1.open(raw_file + "86h.txt", ios::out | ios::app);
	static int line = 0;
	vector<unsigned char> frame_content;
	frame_content.resize(1500);

	static int fback_index = 0;
	int count_86 = 0;
	string timestamp;
	while (getline(inf, s))
	{
		using namespace simig;

		++line;
		//获取时间戳
		if (line == 2) {
			regex ex("\\d{2}:\\d{2}:\\d{2},\\d{3},\\d{3}");
			smatch match;
			regex_search(s, match, ex);
			timestamp = match[0];
		}
		//获取命令内容，可能含有多条命令
		if (line == 3) {
			//cout << s << endl;

			regex ex("\\w{2}");
			auto iter_begin = sregex_iterator(s.begin(), s.end(), ex);
			auto iter_end = sregex_iterator();
			int char_index = 0;
			//将16进制内容存为字符数组
			for (auto iter = iter_begin; iter != iter_end; ++iter, ++char_index)
			{
				string temp = iter->str();
				char hex = decoder::merge_char(temp[0], temp[1]);
				frame_content[char_index] = hex;
			}
			//获取ethernet header
			static command_struct::Eth_Header* eth_header = (command_struct::Eth_Header*)(&frame_content[fback_index]);
			//cout <<hex<< int(eth_header->des_mac.mac1) << '\t' << int(eth_header->source_mac.mac1) << '\t' << eth_header->size << endl;
			fback_index += ETH_HEADER_LENGTH;
			//获取cae_header
			static command_struct::CAE_Header* cae_header = (command_struct::CAE_Header*)(&frame_content[fback_index]);
			//cout << dec << cae_header->byte_count.size << endl;
			fback_index += CAE_HEADER_LENGTH;
			//获取 message number
			static command_struct::Massage_Number* message_number = (command_struct::Massage_Number*)(&frame_content[fback_index]);
			//buffer["message_number"] = message_number->number;
			//cout << hex << message_number->number << endl;
			fback_index += MESSAGE_NUMBER_LENGTH;
			//获取 visual header
			static command_struct::Visual_Header* visual_header = (command_struct::Visual_Header*)(&frame_content[fback_index]);
			//cout << dec << visual_header->first_word.size << endl;
			int visual_size = visual_header->first_word.size;
			fback_index += VISUAL_HEADER_LENGTH;
			//获取commands内容
			int iter = 0;
			if (eth_header->des_mac.mac1 == 0x56) //判断发送源
			{
				while (iter < visual_size) {
					if (frame_content[fback_index] == 0x86) {
						static command_struct::fb_packet_86* pk_fb_86;
						pk_fb_86 = (command_struct::fb_packet_86*)(&frame_content[fback_index]);
						iter += (pk_fb_86->header.first_word.size * 4 + 8);
						fback_index += (pk_fb_86->header.first_word.size * 4 + 8);
						of1 << timestamp << '\t' 
							<< pk_fb_86->header.first_word.opcode<<'\t'
							<< pk_fb_86->header.first_word.channel<<'\t'
							<< pk_fb_86->header.first_word.size<<'\t'
							<< pk_fb_86->header.rts_version.release_no<<'\t'
							<< pk_fb_86->header.rts_version.branch_rev <<'\t'
							<< pk_fb_86->header.rts_version.minor_rev <<'\t'
							<< pk_fb_86->header.rts_version.major_rev <<'\t'
							<< pk_fb_86->flags.vis_on<<'\t'
							<< pk_fb_86->flags.ig_bsl_info_avl << '\t'
							<< pk_fb_86->flags.hostbuf_inh << '\t'
							<< pk_fb_86->flags.collision << '\t'
							<< pk_fb_86->flags.coll_type << '\t'
							<< pk_fb_86->flags.flat_earthdb << '\t'
							<< pk_fb_86->flags.ena_vel << '\t'
							<< pk_fb_86->flags.cord_msk << '\t'
							<< pk_fb_86->flags.gendb_mode << '\t'
							<< pk_fb_86->flags.gen_overwrite << '\t'
							<< pk_fb_86->flags.dbase1_stat << '\t'
							<< pk_fb_86->flags.dbase1_generic << '\t'
							<< pk_fb_86->flags.dbase2_stat << '\t'
							<< pk_fb_86->flags.dbase2_generic << '\t'
							<< DecodeUIntToICAO(pk_fb_86->db1_icao) << '\t'
							<< pk_fb_86->ig_bsl_version.build_ver << '\t'
							<< pk_fb_86->ig_bsl_version.release_ver << '\t'
							<< pk_fb_86->ig_bsl_version.minor_ver << '\t'
							<< pk_fb_86->ig_bsl_version.major_ver << '\t'
							<< decoder::decodeInt2Double(pk_fb_86->db1_lat,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_fb_86->db1_lon,REV1_DEG) << '\t'
							<< decoder::decodeInt2Double(pk_fb_86->db1_ele,HMM_M) << '\t'
							<< pk_fb_86->tod_info.state << '\t'
							<< pk_fb_86->tod_info.ambi_lvl << '\t'
							<< pk_fb_86->tod_info.hr << '\t'
							<< pk_fb_86->tod_info.min << '\t'
							<< pk_fb_86->tod_info.tod_rec << '\t'
							<< pk_fb_86->tod_info.ctod_on << '\t'
							<< pk_fb_86->tod_info.sec << '\t'
							<< std::endl;
					}
					else {
						static command_struct::Command_Header* header;
						header = (command_struct::Command_Header*)(&frame_content[fback_index]);
						iter += (header->first_word.size * 4 + 8);
						fback_index += (header->first_word.size * 4 + 8);
					}
				}
				++count_86;
				if (count_86%50==0)
				{
					std::cout << "86：" << count_86 << std::endl;
				}
				

			}

		}
		if (line == 4) {
			line = 0;
			fback_index = 0;
		}
	}
	inf.close();
	of1.close();
}