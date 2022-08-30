#include "simig_gen_json.h"
#include "simig_decoder.h"
#include <vector>
void simig::command_json::gen_json_21(command_struct::packet_21* pk_21, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_21->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_21->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_21->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_21->header.cs_mask;
	out_json["latitude"] = decoder::decode_lat_lon_40(pk_21->latitude_msw, pk_21->latitude_lsw);
	out_json["longitude"] = decoder::decode_lat_lon_40(pk_21->longitude_msw, pk_21->longitude_lsw);
	out_json["altitude"] = decoder::decodeInt2Double(pk_21->altitude,HMM_M);
	out_json["roll"] = decoder::decodeInt2Double(pk_21->roll,REV1_DEG);
	out_json["pitch"] = decoder::decodeInt2Double(pk_21->pitch,REV1_DEG);
	out_json["yaw"] = decoder::decodeInt2Double(pk_21->yaw,REV1_DEG);
	out_json["delta_latt"] = decoder::decodeInt2Double(pk_21->delta_latt,REV2_DEG);
	out_json["delta_long"] = decoder::decodeInt2Double(pk_21->delta_long,REV2_DEG);
	out_json["delta_alt"] = decoder::decodeInt2Double(pk_21->delta_alt,HMM_M);
	out_json["delta_roll"] = decoder::decodeInt2Double(pk_21->delta_roll,REV1_DEG);
	out_json["delta_pitch"] = decoder::decodeInt2Double(pk_21->delta_pitch,REV1_DEG);
	out_json["delta_yaw"] = decoder::decodeInt2Double(pk_21->delta_yaw,REV1_DEG);
}
void simig::command_json::gen_json_40(command_struct::packet_40* pk_40, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_40->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_40->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_40->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_40->header.cs_mask;
	out_json["control_flags"]["collision_det"] = unsigned int(pk_40->control_flags.collision_det);
	out_json["control_flags"]["nightvis_on"] = unsigned int(pk_40->control_flags.nightvis_on);
	out_json["control_flags"]["flt_freeze"] = unsigned int(pk_40->control_flags.flt_freeze);
	out_json["control_flags"]["crash_ind"] = unsigned int(pk_40->control_flags.crash_ind);
	out_json["control_flags"]["mm_demo"] = unsigned int(pk_40->control_flags.mm_demo);
	out_json["control_flags"]["light_gun"] = unsigned int(pk_40->control_flags.light_gun);
	out_json["control_flags"]["blank1"] = unsigned int(pk_40->control_flags.blank1);
	out_json["control_flags"]["vis_on"] = unsigned int(pk_40->control_flags.vis_on);
	out_json["control_flags"]["blank2"] = unsigned int(pk_40->control_flags.blank2);
	out_json["control_flags"]["chan_off"] = unsigned int(pk_40->control_flags.chan_off);
	out_json["control_flags"]["marsh_malf"] = unsigned int(pk_40->control_flags.marsh_malf);
	out_json["control_flags"]["agnis_malf"] = unsigned int(pk_40->control_flags.agnis_malf);
	out_json["control_flags"]["marsh_arm"] = unsigned int(pk_40->control_flags.marsh_arm);
	out_json["control_flags"]["blank3"] = unsigned int(pk_40->control_flags.blank3);
}
void simig::command_json::gen_json_42(command_struct::packet_42* pk_42, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_42->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_42->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_42->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_42->header.cs_mask;
	out_json["control_flags"]["blank1"] = unsigned int(pk_42->control_flags.blank1);
	out_json["control_flags"]["dbal_load"] = unsigned int(pk_42->control_flags.dbal_load);
	out_json["control_flags"]["autocal_load"] = unsigned int(pk_42->control_flags.autocal_load);
	out_json["control_flags"]["longdb_trans"] = unsigned int(pk_42->control_flags.longdb_trans);
	out_json["control_flags"]["special_gen"] = unsigned int(pk_42->control_flags.special_gen);
	out_json["control_flags"]["ext_rwy"] = unsigned int(pk_42->control_flags.ext_rwy);
	out_json["control_flags"]["blank2"] = unsigned int(pk_42->control_flags.blank2);
	out_json["control_flags"]["static_clutter_off"] = unsigned int(pk_42->control_flags.static_clutter_off);
	out_json["control_flags"]["dynamic_clutter_off"] = unsigned int(pk_42->control_flags.dynamic_clutter_off);
	out_json["control_flags"]["load_6FL"] = unsigned int(pk_42->control_flags.load_6FL);
	out_json["control_flags"]["blank3"] = unsigned int(pk_42->control_flags.blank3);
	out_json["control_flags"]["caltime"] = unsigned int(pk_42->control_flags.caltime);
	out_json["control_flags"]["calrate"] = unsigned int(pk_42->control_flags.calrate);
	out_json["control_flags"]["intensity"] = unsigned int(pk_42->control_flags.intensity);
	out_json["control_flags"]["foview"] = unsigned int(pk_42->control_flags.foview);
	//这里不知道怎么处理，先用原始的int保存数据
	out_json["pri_dbase_msw"] = pk_42->pri_dbase_msw;
	out_json["pri_dbase_lsw"] = pk_42->pri_dbase_lsw;
	//
	out_json["rwy_lattitude"] = decoder::decodeInt2Double(pk_42->rwy_latitude,REV1_DEG);
	out_json["rwy_longitude"] = decoder::decodeInt2Double(pk_42->rwy_longitude,REV1_DEG);
	out_json["rwy_altitude"] = decoder::decodeInt2Double(pk_42->rwy_altitude,HMM_M);
	out_json["rwy_orientation"] =decoder::decodeInt2Double(pk_42->rwy_orientation,REV1_DEG) ;
	out_json["glidescope_ang"] =decoder::decodeInt2Double(pk_42->glidescope_ang,REV1_DEG) ;
	out_json["sec_dbase"] = pk_42->sec_dbase;
	out_json["sec_rwy_lattitude"] = decoder::decodeInt2Double(pk_42->sec_rwy_latitude,REV1_DEG);
	out_json["sec_rwy_longitude"] = decoder::decodeInt2Double( pk_42->sec_rwy_longitude,REV1_DEG);
	out_json["sec_rwy_altitude"] = decoder::decodeInt2Double(pk_42->sec_rwy_altitude,HMM_M);

	out_json["control_flags2"]["repos_flag"] = unsigned int(pk_42->control_flags2.repos_flag);
	out_json["control_flags2"]["gendb_mode"] = unsigned int(pk_42->control_flags2.gendb_mode);
	out_json["control_flags2"]["blank1"] = unsigned int(pk_42->control_flags2.blank1);

}
void simig::command_json::gen_json_44(command_struct::packet_44* pk_44, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_44->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_44->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_44->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_44->header.cs_mask;

	out_json["weather_features"]["wet_rwy"] =unsigned int( pk_44->weather_features.wet_rwy);
	out_json["weather_features"]["icy_rwy"] = unsigned int(pk_44->weather_features.icy_rwy);
	out_json["weather_features"]["snow_rwy"] = unsigned int(pk_44->weather_features.snow_rwy);
	out_json["weather_features"]["slush_rwy"] = unsigned int(pk_44->weather_features.slush_rwy);
	out_json["weather_features"]["patchy_wet"] = unsigned int(pk_44->weather_features.patchy_wet);
	out_json["weather_features"]["patchy_ice"] = unsigned int(pk_44->weather_features.patchy_ice);
	out_json["weather_features"]["tire_marks"] = unsigned int(pk_44->weather_features.tire_marks);
	out_json["weather_features"]["snow_scene"] = unsigned int(pk_44->weather_features.snow_scene);
	out_json["weather_features"]["blw_snow"] = unsigned int(pk_44->weather_features.blw_snow);
	out_json["weather_features"]["cloud1_typ"] = unsigned int(pk_44->weather_features.cloud1_typ);
	out_json["weather_features"]["cloud2_typ"] = unsigned int(pk_44->weather_features.cloud2_typ);
	out_json["weather_features"]["sheet_light"] = unsigned int(pk_44->weather_features.sheet_light);
	out_json["weather_features"]["bolt_light"] = unsigned int(pk_44->weather_features.bolt_light);
	out_json["weather_features"]["si_rainlvl"] = unsigned int(pk_44->weather_features.si_rainlvl);
	out_json["weather_features"]["blank1"] = unsigned int(pk_44->weather_features.blank1);
	out_json["weather_features"]["high_cld"] = unsigned int(pk_44->weather_features.high_cld);
	out_json["weather_features"]["turb_cld"] = unsigned int(pk_44->weather_features.turb_cld);
	out_json["weather_features"]["blank2"] = unsigned int(pk_44->weather_features.blank2);
	out_json["weather_features"]["contaminants"] = unsigned int(pk_44->weather_features.contaminants);
	out_json["n_gust_wind"] = pk_44->n_gust_wind;
	out_json["e_gust_wind"] = pk_44->e_gust_wind;
	out_json["rwy_surface"] = unsigned int(pk_44->rwy_surface);
	out_json["cld1_octa"] = unsigned int(pk_44->cld1_octa);
	out_json["cld2_octa"] = unsigned int(pk_44->cld2_octa);
	out_json["colour"] = unsigned int(pk_44->colour);
	out_json["rain_lvl"] = unsigned int(pk_44->rain_lvl);
	out_json["n_wind"] = pk_44->n_wind;
	out_json["e_wind"] = pk_44->e_wind;
}
void simig::command_json::gen_json_43(command_struct::packet_43* pk_43, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_43->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_43->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_43->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_43->header.cs_mask;

	out_json["ship_lights"]["nose_taxi"] = unsigned int(pk_43->ship_lights.nose_taxi);
	out_json["ship_lights"]["blank1"] = unsigned int(pk_43->ship_lights.blank1);
	out_json["ship_lights"]["l_turnoff"] = unsigned int(pk_43->ship_lights.l_turnoff);
	out_json["ship_lights"]["r_turnoff"] = unsigned int(pk_43->ship_lights.r_turnoff);
	out_json["ship_lights"]["nose_land"] = unsigned int(pk_43->ship_lights.nose_land);
	out_json["ship_lights"]["l_inboard"] = unsigned int(pk_43->ship_lights.l_inboard);
	out_json["ship_lights"]["r_inboard"] = unsigned int(pk_43->ship_lights.r_inboard);
	out_json["ship_lights"]["l_outboard"] = unsigned int(pk_43->ship_lights.l_outboard);
	out_json["ship_lights"]["r_outboard"] = unsigned int(pk_43->ship_lights.r_outboard);
	out_json["ship_lights"]["wingtip_strobe"] = unsigned int(pk_43->ship_lights.wingtip_strobe);
	out_json["ship_lights"]["anti_coll_beac"] = unsigned int(pk_43->ship_lights.anti_coll_beac);
	out_json["ship_lights"]["taxiway"] = unsigned int(pk_43->ship_lights.taxiway);
	out_json["ship_lights"]["gr1_environ"] = unsigned int(pk_43->ship_lights.gr1_environ);
	out_json["ship_lights"]["gr2_environ"] = unsigned int(pk_43->ship_lights.gr2_environ);
	out_json["ship_lights"]["gr3_environ"] = unsigned int(pk_43->ship_lights.gr3_environ);
	out_json["ship_lights"]["gr4_environ"] = unsigned int(pk_43->ship_lights.gr4_environ);
	out_json["ship_lights"]["gear_down"] = unsigned int(pk_43->ship_lights.gear_down);
	out_json["ship_lights"]["perimeter_lts"] = unsigned int(pk_43->ship_lights.perimeter_lts);
	out_json["ship_lights"]["blank2"] = unsigned int(pk_43->ship_lights.blank2);
	out_json["ship_lights"]["autolight_dis"] = unsigned int(pk_43->ship_lights.autolight_dis);
	out_json["ship_lights"]["random_int"] = unsigned int(pk_43->ship_lights.random_int);
	std::vector<configor::json> rawy_lights;
	for (int i=0;i<16;++i)
	{
	    configor::json temp;
		temp["approach"] = unsigned int(pk_43->rwy_lights[i].approach);
		temp["edge"] = unsigned int(pk_43->rwy_lights[i].edge);
		temp["centerline"] = unsigned int(pk_43->rwy_lights[i].centerline);
		temp["td_zone"] = unsigned int(pk_43->rwy_lights[i].td_zone);
		temp["strobe"] = unsigned int(pk_43->rwy_lights[i].strobe);
		temp["vasi_papi"] = unsigned int(pk_43->rwy_lights[i].vasi_papi);
		temp["reils"] = unsigned int(pk_43->rwy_lights[i].reils);
		temp["sec_app"] = unsigned int(pk_43->rwy_lights[i].sec_app);
		temp["lahso_lt"] = unsigned int(pk_43->rwy_lights[i].lahso_lt);
		temp["thl_lt"] = unsigned int(pk_43->rwy_lights[i].thl_lt);
		temp["rel_lt"] = unsigned int(pk_43->rwy_lights[i].rel_lt);
		rawy_lights.push_back(temp);
	}
	out_json["rawy_lights"] = rawy_lights;
	out_json["ap_control"]["ap_beac"] = unsigned int(pk_43->ap_control.ap_beac);
	out_json["ap_control"]["aim_point"] = unsigned int(pk_43->ap_control.aim_point);
	out_json["ap_control"]["rf_rwy"] = unsigned int(pk_43->ap_control.rf_rwy);
	out_json["ap_control"]["at_taxi"] = unsigned int(pk_43->ap_control.at_taxi);
	out_json["ap_control"]["st_bar"] = unsigned int(pk_43->ap_control.st_bar);
	out_json["ap_control"]["man_stop"] = unsigned int(pk_43->ap_control.man_stop);
	out_json["ap_control"]["atgs_route"] = unsigned int(pk_43->ap_control.atgs_route);
	out_json["ap_control"]["dock_mes"] = unsigned int(pk_43->ap_control.dock_mes);
	out_json["ap_control"]["blank1"] = unsigned int(pk_43->ap_control.blank1);
	out_json["ap_control"]["beac_col"] = unsigned int(pk_43->ap_control.beac_col);
	out_json["ap_control"]["blank2"] = unsigned int(pk_43->ap_control.blank2);
}
void simig::command_json::gen_json_45(command_struct::packet_45* pk_45, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_45->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_45->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_45->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_45->header.cs_mask;
	//单位 feet
	out_json["rwy_min_vis"] = pk_45->rwy_min_vis;
	out_json["rwy_max_vis"] = pk_45->rwy_max_vis;
	out_json["fog_top_l"] = pk_45->fog_top_l;
	out_json["fog_top_u"] = pk_45->fog_top_u;
	out_json["blw_cld_vis"] = pk_45->blw_cld_vis;
	out_json["cld1_base_l"] = pk_45->cld1_base_l;
	out_json["cld1_base_u"] = pk_45->cld1_base_u;
	out_json["cld1_min_vis"] = pk_45->cld1_min_vis;
	out_json["cld1_max_vis"] = pk_45->cld1_max_vis;
	out_json["cld1_top_l"] = pk_45->cld1_top_l;
	out_json["cld1_top_u"] = pk_45->cld1_top_u;
	out_json["btw_cld_vis"] = pk_45->btw_cld_vis;
	out_json["cld2_base_l"] = pk_45->cld2_base_l;
	out_json["cld2_base_u"] = pk_45->cld2_base_u;
	out_json["cld2_min_vis"] = pk_45->cld2_min_vis;
	out_json["cld2_max_vis"] = pk_45->cld2_max_vis;
	out_json["cld2_top_l"] = pk_45->cld2_top_l;
	out_json["cld2_top_u"] = pk_45->cld2_top_u;
	out_json["abv_cld_vis"] = pk_45->abv_cld_vis;
	//这里标的解释为0-7，意思是粒度为多少，哪位就是1？
	out_json["granularity"]["fog"] =unsigned int(pk_45->granularity.fog);
	out_json["granularity"]["fog_top"] = unsigned int(pk_45->granularity.fog_top);
	out_json["granularity"]["cld1_base"] = unsigned int(pk_45->granularity.cld1_base);
	out_json["granularity"]["cld1"] = unsigned int(pk_45->granularity.cld1);
	out_json["granularity"]["cld1_top"] = unsigned int(pk_45->granularity.cld1_top);
	out_json["granularity"]["cld2_base"] = unsigned int(pk_45->granularity.cld2_base);
	out_json["granularity"]["cld2"] = unsigned int(pk_45->granularity.cld2);
	out_json["granularity"]["cld2_top"] = unsigned int(pk_45->granularity.cld2_top);
	//
	out_json["gnd_height"] = pk_45->gnd_height;
	out_json["modifier"] = pk_45->modifier;
}
void simig::command_json::gen_json_47(command_struct::packet_47* pk_47, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_47->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_47->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_47->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_47->header.cs_mask;
	//(0=day, 1=night, 2=dusk, 3=dawn)
	out_json["illum_bits"]["tod"] = unsigned int(pk_47->illum_bits.tod);
	// (0=Off, 1=On)
	out_json["illum_bits"]["sun_on"] = unsigned int(pk_47->illum_bits.sun_on);
	//(0 = Off, 1 = On)
	out_json["illum_bits"]["moon_on"] = unsigned int(pk_47->illum_bits.moon_on);
	//(0 - 5)
	out_json["illum_bits"]["horizon_glow"] = unsigned int(pk_47->illum_bits.horizon_glow);
	//0-7
	out_json["illum_bits"]["moon_phase"] = unsigned int(pk_47->illum_bits.moon_phase);
	out_json["illum_bits"]["moon_phase_override"] = unsigned int(pk_47->illum_bits.moon_phase_override);
	out_json["illum_bits"]["blank1"] = unsigned int(pk_47->illum_bits.blank1);
	//0-59
	out_json["illum_bits"]["minute"] = unsigned int(pk_47->illum_bits.minute);
	//0-23
	out_json["illum_bits"]["hour"] = unsigned int(pk_47->illum_bits.hour);
	//1-31
	out_json["illum_bits"]["day"] = unsigned int(pk_47->illum_bits.day);
	//1-12
	out_json["illum_bits"]["month"] = unsigned int(pk_47->illum_bits.month);
	//0-59
	out_json["illum_bits"]["seconds"] = unsigned int(pk_47->illum_bits.seconds);
	out_json["illum_bits"]["hst_todsnt_flg"] = unsigned int(pk_47->illum_bits.hst_todsnt_flg);
	out_json["illum_bits"]["vis_timrec_flg"] = unsigned int(pk_47->illum_bits.vis_timrec_flg);
	out_json["illum_bits"]["blank2"] = unsigned int(pk_47->illum_bits.blank2);
}
void simig::command_json::gen_json_52(command_struct::packet_52* pk_52, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_52->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_52->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_52->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_52->header.cs_mask;
	out_json["request_data"]["id_num"] = unsigned int(pk_52->request_data.id_num);
	out_json["request_data"]["blank1"] = unsigned int(pk_52->request_data.blank1);
	out_json["request_data"]["virt_ch_num"] = unsigned int(pk_52->request_data.virt_ch_num);
	//(00h HAT perpendicular) (02h HOG vertical)(04h HAT vertical)(08h WA)(40h CD point)
	out_json["request_data"]["category"] = unsigned int(pk_52->request_data.category);
	//单位1/2mm
	out_json["x"] = decoder::decodeInt2Double(pk_52->x,HMM_M);
	out_json["y"] = decoder::decodeInt2Double(pk_52->y,HMM_M);
	out_json["z"] = decoder::decodeInt2Double(pk_52->z,HMM_M);
}
void simig::command_json::gen_json_55(command_struct::packet_55* pk_55, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_55->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_55->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_55->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_55->header.cs_mask;
	//( 0 = Off, 1 = Snow, 2 = Rain )
	out_json["snow_control_bits"]["falling"] = unsigned int(pk_55->snow_control_bits.falling);
	//单位knot
	out_json["snow_control_bits"]["velocity"] = unsigned int(pk_55->snow_control_bits.velocity);
}

void simig::command_json::gen_json_82(command_struct::fb_packet_82* pk_fb_82, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_fb_82->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_fb_82->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_fb_82->header.first_word.size);
	out_json["header"]["cs_mask"] = pk_fb_82->header.cs_mask;
	out_json["hat_info"]["id"] = unsigned int(pk_fb_82->hat_info.id);
	out_json["hat_info"]["blank1"] = unsigned int(pk_fb_82->hat_info.blank1);
	out_json["hat_info"]["channel"] = unsigned int(pk_fb_82->hat_info.channel);
	out_json["hat_info"]["category"] = unsigned int(pk_fb_82->hat_info.category);
	out_json["material"] = pk_fb_82->material;
	out_json["equation_Nx"] = pk_fb_82->equation_Nx/(POW2_31-1.0);
	out_json["equation_Ny"] = pk_fb_82->equation_Ny/(POW2_31 - 1.0);
	out_json["equation_Nz"] = pk_fb_82->equation_Nz/(POW2_31 - 1.0);
	out_json["equation_D"] = decoder::decodeInt2Double(pk_fb_82->equation_D,HMM_M);
	out_json["hat"] = decoder::decodeInt2Double(pk_fb_82->hat,HMM_M);
}
void simig::command_json::gen_json_86(command_struct::fb_packet_86* pk_fb_86, configor::json& out_json) {
	out_json["header"]["opcode"] = unsigned int(pk_fb_86->header.first_word.opcode);
	out_json["header"]["channel"] = unsigned int(pk_fb_86->header.first_word.channel);
	out_json["header"]["size"] = unsigned int(pk_fb_86->header.first_word.size);
	out_json["header"]["rts_version"]["release_no"] = unsigned int (pk_fb_86->header.rts_version.release_no);
	out_json["header"]["rts_version"]["branch_rev"] = unsigned int(pk_fb_86->header.rts_version.branch_rev);
	out_json["header"]["rts_version"]["minor_rev"] = unsigned int(pk_fb_86->header.rts_version.minor_rev);
	out_json["header"]["rts_version"]["major_rev"] = unsigned int(pk_fb_86->header.rts_version.major_rev);

	out_json["flags"]["vis_on"] = unsigned int(pk_fb_86->flags.vis_on);
	out_json["flags"]["blank1"] = unsigned int(pk_fb_86->flags.blank1);
	out_json["flags"]["ig_bsl_info_avl"] = unsigned int(pk_fb_86->flags.ig_bsl_info_avl);
	out_json["flags"]["hostbuf_inh"] = unsigned int(pk_fb_86->flags.hostbuf_inh);
	out_json["flags"]["collision"] = unsigned int(pk_fb_86->flags.collision);
	out_json["flags"]["coll_type"] = unsigned int(pk_fb_86->flags.coll_type);
	out_json["flags"]["blank2"] = unsigned int(pk_fb_86->flags.blank2);
	out_json["flags"]["flat_earthdb"] = unsigned int(pk_fb_86->flags.flat_earthdb);
	out_json["flags"]["ena_vel"] = unsigned int(pk_fb_86->flags.ena_vel);
	out_json["flags"]["cord_msk"] = unsigned int(pk_fb_86->flags.cord_msk);
	out_json["flags"]["blank3"] = unsigned int(pk_fb_86->flags.blank3);
	out_json["flags"]["gendb_mode"] = unsigned int(pk_fb_86->flags.gendb_mode);
	out_json["flags"]["gen_overwrite"] = unsigned int(pk_fb_86->flags.gen_overwrite);
	out_json["flags"]["blank4"] = unsigned int(pk_fb_86->flags.blank4);
	out_json["flags"]["dbase1_stat"] = unsigned int(pk_fb_86->flags.dbase1_stat);
	out_json["flags"]["dbase1_generic"] = unsigned int(pk_fb_86->flags.dbase1_generic);
	out_json["flags"]["dbase2_stat"] = unsigned int(pk_fb_86->flags.dbase2_stat);
	out_json["flags"]["dbase2_generic"] = unsigned int(pk_fb_86->flags.dbase2_generic);

	out_json["db1_icao"] = pk_fb_86->db1_icao;

	out_json["ig_bsl_version"]["build_ver"] = unsigned int(pk_fb_86->ig_bsl_version.build_ver);
	out_json["ig_bsl_version"]["release_ver"] = unsigned int(pk_fb_86->ig_bsl_version.release_ver);
	out_json["ig_bsl_version"]["minor_ver"] = unsigned int(pk_fb_86->ig_bsl_version.minor_ver);
	out_json["ig_bsl_version"]["major_ver"] = unsigned int(pk_fb_86->ig_bsl_version.major_ver);

	out_json["db1_lat"] = decoder::decodeInt2Double(pk_fb_86->db1_lat,REV1_DEG);
	out_json["db1_lon"] = decoder::decodeInt2Double(pk_fb_86->db1_lon,REV1_DEG);
	out_json["db1_ele"] = decoder::decodeInt2Double(pk_fb_86->db1_ele,HMM_M);
	out_json["eyept_cs"] = pk_fb_86->eyept_cs;

	out_json["tod_info"]["state"] = unsigned int(pk_fb_86->tod_info.state);
	out_json["tod_info"]["ambi_lvl"] = unsigned int(pk_fb_86->tod_info.ambi_lvl);
	out_json["tod_info"]["hr"] = unsigned int(pk_fb_86->tod_info.hr);
	out_json["tod_info"]["blank1"] = unsigned int(pk_fb_86->tod_info.blank1);
	out_json["tod_info"]["min"] = unsigned int(pk_fb_86->tod_info.min);
	out_json["tod_info"]["blank2"] = unsigned int(pk_fb_86->tod_info.blank2);
	out_json["tod_info"]["tod_rec"] = unsigned int(pk_fb_86->tod_info.tod_rec);
	out_json["tod_info"]["ctod_on"] = unsigned int(pk_fb_86->tod_info.ctod_on);
	out_json["tod_info"]["sec"] = unsigned int(pk_fb_86->tod_info.sec);
}
