// simig_decoder.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#define  POW2_31           2147483648.0
#define  POW2_32           4294967295.0       /* 2^32         */
#define  REV1_DEG          8.38190317155e-8
#define  REV2_DEG          3.27418092638254e-10 /*360/2^40*/
#define  HMM_M             0.0005
#define  M_HMM             2000.0
#define  ETH_HEADER_LENGTH 14
#define  CAE_HEADER_LENGTH 16
#define  MESSAGE_NUMBER_LENGTH 4
#define  VISUAL_HEADER_LENGTH  8
namespace simig {
	namespace command_struct {
		typedef struct ETHERNET_HEADER{
			struct  
			{
				unsigned char mac1;
				unsigned char mac2;
				unsigned char mac3;
				unsigned char mac4;
				unsigned char mac5;
				unsigned char mac6;

			}des_mac;
			struct
			{
				unsigned char mac1;
				unsigned char mac2;
				unsigned char mac3;
				unsigned char mac4;
				unsigned char mac5;
				unsigned char mac6;
			}source_mac;
			unsigned short size;
		}Eth_Header;

		typedef struct CAE_HEADER {
			unsigned int first_word;
			struct {
				unsigned int size : 16; //0-15
				unsigned int other : 16;//16-31
			}byte_count;
			unsigned int third_word;
			struct  
			{
				unsigned int flag : 8;    //0-7
				unsigned int other : 24;  //8-31
			}cont_flag;
		}CAE_Header;

		typedef struct MESSAGE_NUMBER {
			unsigned int number;
		}Massage_Number;

		typedef struct VISUAL_HEADER
		{
			struct 
			{
				unsigned int size : 16; 
				unsigned int opcode : 16;
			}first_word;
			unsigned int second_word;
		}Visual_Header;

		typedef struct COMMAND_HEADER
		{
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int   opcode : 8;    /*   0- 7 */
				unsigned int   channel : 8;    /*   8-15 */
				unsigned int   size : 16;    /*  16-31 */
			} first_word;

			int            cs_mask;
		} Command_Header;

		typedef struct FB_COMMAND_HEADER_86
		{
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int   opcode : 8;    /*   0- 7 */
				unsigned int   channel : 8;    /*   8-15 */
				unsigned int   size : 16;    /*  16-31 */
			} first_word;

			struct
			{
				unsigned int   release_no : 12;    /*  0 -11 */
				unsigned int   branch_rev : 4;     /*  12-15 */
				unsigned int   minor_rev : 8;     /*  16-23 */
				unsigned int   major_rev : 8;     /*  24-31 */
			} rts_version;
		} Fb_Command_Header_86;

		typedef struct PACKET_21
		{
			Command_Header         header;
			unsigned int   latitude_msw;
			unsigned int   latitude_lsw;
			unsigned int   longitude_msw;
			unsigned int   longitude_lsw;
			int            altitude;
			int            roll;
			int            pitch;
			int            yaw;
			int            delta_latt;
			int            delta_long;
			int            delta_alt;
			int            delta_roll;
			int            delta_pitch;
			int            delta_yaw;

		} packet_21;

		typedef struct PACKET_40
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int   collision_det : 1;    /*     0  */
				unsigned int   nightvis_on : 1;    /*     1  */
				unsigned int   flt_freeze : 1;    /*     2  */
				unsigned int   crash_ind : 1;    /*     3  */
				unsigned int   mm_demo : 1;    /*     4  */
				unsigned int   light_gun : 3;    /*  5-7   */
				unsigned int   blank1: 4;    /*  8-11  */
				unsigned int   vis_on : 2;    /* 12-13  */
				unsigned int   blank2: 1;    /*    14  */
				unsigned int   chan_off : 1;    /*    15  */
				unsigned int   marsh_malf : 1;    /*    16  */
				unsigned int   agnis_malf : 1;    /*    17  */
				unsigned int   marsh_arm : 2;    /* 18-19  */
				unsigned int   blank3: 12;    /* 20-31  */

			} control_flags;

		} packet_40;

		typedef struct PACKET_42
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  blank1: 5;    /*   0-4  */
				unsigned int  dbal_load : 1;    /*     5  */
				unsigned int  autocal_load : 1;    /*     6  */
				unsigned int  longdb_trans : 1;    /*     7  */
				unsigned int  special_gen : 4;    /*  8-11  */
				unsigned int  ext_rwy : 1;    /* 12     */
				unsigned int  blank2: 7;    /* 13-19  */
				unsigned int  static_clutter_off : 1;    /* 20     */
				unsigned int  dynamic_clutter_off : 1;    /* 21     */
				unsigned int  load_6FL : 1;    /*  22    */
				unsigned int  blank3: 1;    /*  23    */
				unsigned int  caltime : 3;    /* 24-26  */
				unsigned int  calrate : 1;    /*    27  */
				unsigned int  intensity : 2;    /* 28-29  */
				unsigned int  foview : 2;    /* 30-31  */

			} control_flags;

			int            pri_dbase_msw;
			int            pri_dbase_lsw;
			int            rwy_latitude;
			int            rwy_longitude;
			int            rwy_altitude;
			int            rwy_orientation;
			int            glidescope_ang;
			int            sec_dbase;
			int            sec_rwy_latitude;
			int            sec_rwy_longitude;
			int            sec_rwy_altitude;
			struct
			{
				unsigned int  repos_flag : 1;    /*     0  */
				unsigned int  gendb_mode : 2;    /*    1-2 */
				unsigned int  blank1: 29;   /*    3-31*/
			} control_flags2;

		} packet_42;

		typedef struct PACKET_43
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  nose_taxi : 1;    /*     0  */
				unsigned int  blank1: 2;    /*   1-2  */
				unsigned int  l_turnoff : 1;    /*     3  */
				unsigned int  r_turnoff : 1;    /*     4  */
				unsigned int  nose_land : 1;    /*     5  */
				unsigned int  l_inboard : 1;    /*     6  */
				unsigned int  r_inboard : 1;    /*     7  */
				unsigned int  l_outboard : 1;    /*     8  */
				unsigned int  r_outboard : 1;    /*     9  */
				unsigned int  wingtip_strobe : 1;    /*    10  */
				unsigned int  anti_coll_beac : 1;    /*    11  */
				unsigned int  taxiway : 4;    /* 12-15  */
				unsigned int  gr1_environ : 4;    /* 16-19  */
				unsigned int  gr2_environ : 4;    /* 20-23  */
				unsigned int  gr3_environ : 4;    /* 24-27  */
				unsigned int  gr4_environ : 4;    /* 28-31  */

				/* new word */

				unsigned int  gear_down : 1;    /*     0  */
				unsigned int  perimeter_lts : 4;    /*  1-4   */
				unsigned int  blank2: 25;   /*  5-29  */
				unsigned int  autolight_dis : 1;    /*    30  */
				unsigned int  random_int : 1;    /*    31  */

			} ship_lights;

			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int    approach : 4;    /*   0-3 */
				unsigned int    edge : 4;    /*   4-7 */
				unsigned int    centerline : 4;    /*   8-11 */
				unsigned int    td_zone : 4;    /*  12-15 */
				unsigned int    strobe : 4;    /*  16-19 */
				unsigned int    vasi_papi : 4;    /*  20-23 */
				unsigned int    reils : 4;    /*  24-27 */
				unsigned int    sec_app : 1;    /*  28    */
				unsigned int    lahso_lt : 1;    /*  29    */
				unsigned int    thl_lt : 1;    /*  30 */
				unsigned int    rel_lt : 1;    /*  31 */
			} rwy_lights[16];

			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int    ap_beac : 1;    /*      0 */
				unsigned int    aim_point : 3;    /*    1-3 */
				unsigned int    rf_rwy : 8;    /*      4 */
				unsigned int    at_taxi : 1;    /*     12 */
				unsigned int    st_bar : 1;    /*     13 */
				unsigned int    man_stop : 1;    /*     14 */
				unsigned int    atgs_route : 9;    /*  15-23 */
				unsigned int    dock_mes : 1;    /*     24 */
				unsigned int    blank1: 3;    /*  25-27 */
				unsigned int    beac_col : 2;    /*  28-29 */
				unsigned int    blank2: 2;    /*  30-31 */

			}  ap_control;

		}   packet_43;

		typedef struct PACKET_44
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  wet_rwy : 1;    /*     0  */
				unsigned int  icy_rwy : 1;    /*     1  */
				unsigned int  snow_rwy : 1;    /*     2  */
				unsigned int  slush_rwy : 1;    /*     3  */
				unsigned int  patchy_wet : 1;    /*     4  */
				unsigned int  patchy_ice : 1;    /*     5  */
				unsigned int  tire_marks : 1;    /*     6  */
				unsigned int  snow_scene : 1;    /*     7  */
				unsigned int  blw_snow : 1;    /*     8  */
				unsigned int  cloud1_typ : 2;    /*  9-10  */
				unsigned int  cloud2_typ : 2;    /* 11-12  */
				unsigned int  sheet_light : 1;    /* 13     */
				unsigned int  bolt_light : 1;    /* 14     */
				unsigned int  si_rainlvl : 3;    /* 15-17  */
				unsigned int  blank1: 4;    /* 18-21  */
				unsigned int  high_cld : 2;    /* 22-23  */
				unsigned int  turb_cld : 2;    /* 24-25  */
				unsigned int  blank2: 1;    /* 26     */
				unsigned int  contaminants : 5;    /* 27-31  */

			} weather_features;

			int            n_gust_wind;
			int            e_gust_wind;

			unsigned int   rwy_surface : 8;    /*  0-7   */
			unsigned int   cld1_octa : 4;    /*  8-11  */
			unsigned int   cld2_octa : 4;    /* 12-15  */
			unsigned int   colour : 8;    /* 16-23  */
			unsigned int   rain_lvl : 8;    /* 24-31  */

			int            n_wind;
			int            e_wind;

		}   packet_44;

		typedef struct PACKET_45
		{
			Command_Header         header;
			int            rwy_min_vis;
			int            rwy_max_vis;
			int            fog_top_l;
			int            fog_top_u;
			int            blw_cld_vis;
			int            cld1_base_l;
			int            cld1_base_u;
			int            cld1_min_vis;
			int            cld1_max_vis;
			int            cld1_top_l;
			int            cld1_top_u;
			int            btw_cld_vis;
			int            cld2_base_l;
			int            cld2_base_u;
			int            cld2_min_vis;
			int            cld2_max_vis;
			int            cld2_top_l;
			int            cld2_top_u;
			int            abv_cld_vis;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  fog : 8;   /*   0- 7  */
				unsigned int  fog_top : 8;   /*   8-15  */
				unsigned int  cld1_base : 8;   /*  16-23  */
				unsigned int  cld1 : 8;   /*  24-31  */
				/* new word */
				unsigned int  cld1_top : 8;   /*   0- 7  */
				unsigned int  cld2_base : 8;   /*   8-15  */
				unsigned int  cld2 : 8;   /*  16-23  */
				unsigned int  cld2_top : 8;   /*  24-31  */

			} granularity;

			int            gnd_height;
			int            modifier;

		} packet_45;

		typedef struct PACKET_47
		{
			Command_Header         header;
			struct                                 /* Bit Width,  Bits #  */
			{
				unsigned int   tod : 2;   /*   0- 1  */
				unsigned int   sun_on : 1;   /*      2  */
				unsigned int   moon_on : 1;   /*      3  */
				unsigned int   horizon_glow : 4;   /*   4- 7  */
				unsigned int   moon_phase : 4;   /*   8-11  */
				unsigned int   moon_phase_override : 1;   /*     12  */
				unsigned int   blank1: 19;   /*  13-31  */
				/* new word */
				unsigned int   minute : 8;   /*   0- 7  */
				unsigned int   hour : 8;   /*   8-15  */
				unsigned int   day : 8;   /*  16-23  */
				unsigned int   month : 8;   /*  24-31  */
				/* new word */
				unsigned int   seconds : 8;   /*   0- 7  */
				unsigned int   hst_todsnt_flg : 1;   /*      8  */
				unsigned int   vis_timrec_flg : 1;   /*      9  */
				unsigned int   blank2: 22;   /*  10-31  */

			} illum_bits;

		} packet_47;

		typedef struct PACKET_52
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  id_num : 12;    /*  0-11  */
				unsigned int  : 9;    /* 12-20  */
				unsigned int  virt_ch_num : 3;    /* 21-23  */
				unsigned int  category : 8;    /* 24-31  */

			} request_data;

			int            x;
			int            y;
			int            z;

		} packet_52;
		// 
		typedef struct PACKET_55
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  falling : 16;    /*  0-15  */
				unsigned int  velocity : 16;    /* 16-31  */
			}  snow_control_bits;

		} packet_55;

		typedef struct FB_PACKET_86
		{
			Fb_Command_Header_86    header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  vis_on : 1;    /*     0  */
				unsigned int  : 1;    /*     1  */
				unsigned int  ig_bsl_info_avl : 1;    /*     2  */
				unsigned int  hostbuf_inh : 1;    /*     3  */
				unsigned int  collision : 1;    /*     4  */
				unsigned int  coll_type : 2;    /*  5- 6  */
				unsigned int  : 3;    /*  7- 9  */
				unsigned int  flat_earthdb : 1;    /*    10  */
				unsigned int  ena_vel : 1;    /*    11  */
				unsigned int  cord_msk : 1;    /*    12  */
				unsigned int  : 4;    /* 13-16  */
				unsigned int  gendb_mode : 3;    /* 17-19  */
				unsigned int  gen_overwrite : 1;    /* 20     */
				unsigned int  : 3;    /* 21-23  */
				unsigned int  dbase1_stat : 3;    /* 24-26  */
				unsigned int  dbase1_generic : 1;    /*    27  */
				unsigned int  dbase2_stat : 3;    /* 28-30  */
				unsigned int  dbase2_generic : 1;    /*    31  */

			} flags;

			int          db1_icao;
			struct
			{
				unsigned int   build_ver : 4;     /*  0 - 3 */
				unsigned int   release_ver : 12;    /*  4 -15 */
				unsigned int   minor_ver : 8;     /*  16-23 */
				unsigned int   major_ver : 8;     /*  24-31 */
			} ig_bsl_version;
			int          db1_lat;
			int          db1_lon;
			int          db1_ele;
			int          eyept_cs;
			struct                      /* Bit Width,  Bits #  */
			{
				//(0 = Day, 1 = Night, 2 = Dusk,3=dawn)
				unsigned int  state : 2;    /*  0- 1  */
				//(0-63)
				unsigned int  ambi_lvl : 6;    /*  2- 7  */
				unsigned int  hr : 5;    /*  8-12  */
				unsigned int  : 3;    /* 13-15  */
				unsigned int  min : 6;    /* 16-21  */
				unsigned int  : 2;    /* 22-23  */
				unsigned int  tod_rec : 1;    /*    24  */
				unsigned int  ctod_on : 1;    /*    25  */
				unsigned int  sec : 6;    /* 26-31  */


			} tod_info;

		} fb_packet_86;
		typedef struct FB_PACKET_82
		{
			Command_Header         header;
			struct                      /* Bit Width,  Bits #  */
			{
				unsigned int  id : 12;    /*  0-11  */
				unsigned int  : 9;    /* 12-20  */
				unsigned int  channel : 3;    /* 21-23  */
				unsigned int  category : 8;    /* 24-31  */

			} hat_info;

			int            material;
			int            equation_Nx;
			int            equation_Ny;
			int            equation_Nz;
			int            equation_D;
			int            hat;

		} fb_packet_82;
	}

}


// TODO: 在此处引用程序需要的其他标头。
