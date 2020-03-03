#include "yingxue_wifi.h"
#include "scene.h"

extern struct yingxue_base_tag yingxue_base;

//测试数据
const uint8_t test_buf[] = { 0xfc, 0x00, 0x01, 0x08, 0x01, 0x06 };
//const uint8_t test_buf[] = { 0xfc, 0x00, 0x00, 0x00, 0xfc };


//设备信息上报
const uint8_t to_wifi_info[] = { 
	0xFC, 0x00, 0x2D, 0x02, 0x01, 0x06, 0x6D, 0x67, 0x62, 0x69, 
	0x74, 0x65, 0x20, 0x33, 0x30, 0x31, 0x31, 0x35, 0x32, 0x65,
	0x33, 0x36, 0x33, 0x38, 0x62, 0x34, 0x39, 0x30, 0x31, 0x39, 
	0x62, 0x64, 0x31, 0x64, 0x35, 0x32, 0x64, 0x35, 0x33, 0x32, 
	0x64, 0x38, 0x31, 0x38, 0x39, 0x01, 0x00, 0x00, 0x01, 0x98 };
//配网
const uint8_t to_wifi_net[] = { 0xfc, 0x00, 0x01, 0x08, 0x01, 0x06 };

//心跳fc 00 02 03 05 00 06



//定义一个缓存数据
struct wifi_cache_tag wifi_cache_g;
//定义一个接受到数据
struct wifi_frame_tag wifi_frame_g;

//初始化wifi
void 
yingxue_wifi_init()
{

	//初始化缓存数据
	memset(&wifi_cache_g, 0, sizeof(struct wifi_cache_tag));
	//初始化接受数据
	memset(&wifi_frame_g, 0, sizeof(struct wifi_frame_tag));


}

//从缓存中分析数据，并且验证正确性
//return 0错误 1正确
int 
yingxue_wifi_data_check(struct wifi_cache_tag *wifi_cache, struct wifi_frame_tag *wifi_frame)
{
	uint8_t *p_data = wifi_cache->data;
	uint16_t data_len = wifi_cache->data_len;
	uint8_t check_no = 0; //验证码
	uint8_t out_check_len = 0; //除去验证码的总长度
	//判断头是否是0xfc
	if (p_data[0] != 0xfc){
		CLEAN_WIFI_CACHE(wifi_cache);
		return 0;
	}
	//效验码是否正确

	GET_CHECK_VAL(wifi_cache, check_no);

	//验证码错误
	if (check_no != p_data[wifi_cache->idx - 1]){
		CLEAN_WIFI_CACHE(wifi_cache);
		return 0;
	}

	//得到一个完整的帧
	//得到命令
	wifi_frame->command = p_data[3];
	wifi_frame->data_len = data_len;

	//如何命令数据是0x00,就是ack
	if (wifi_frame->command != 0x00){
		memmove(wifi_frame->data, wifi_cache->data + 4, wifi_cache->data_len);
	}
	CLEAN_WIFI_CACHE(wifi_cache);
	return 1;
}


//串口接受数据
//@param 环形列表头
int 
yingxue_wifi_data_from_wifi()
{
	uint8_t rece_buf[20];
	uint8_t len = 0;
	uint8_t flag = 0;
#ifdef _WIN32
	//读出的数据进入环形队列
	//in_chain_list(p_chain_list, data);
	len = sizeof(test_buf);
	memmove(rece_buf, test_buf, len);
#else
#endif
	//如果接受到数据进入分析
	if (len){
		for (int i = 0; i < len; i++){
			//写入缓存
			wifi_cache_g.data[wifi_cache_g.idx] = rece_buf[i];
			wifi_cache_g.idx += 1;
			//写入数据长度
			if (wifi_cache_g.idx == 4){
				wifi_cache_g.data_len = (wifi_cache_g.data[1] << 8) | (wifi_cache_g.data[2]);
			}
			//数据读取完成,头+命令+长度+效验 = 5
			if (wifi_cache_g.idx == 5 + wifi_cache_g.data_len){
				//进入数据校正
				flag = yingxue_wifi_data_check(&wifi_cache_g, &wifi_frame_g);
			}
			//超过最大值舍去所有数据
			if (wifi_cache_g.idx >= MAX_CACHE_NUM){
				CLEAN_WIFI_CACHE((&wifi_cache_g));
			}
			//如果得到一个完整的帧，开始分析帧
			if (flag == 1){

				//分别解析


				printf("frame ok\n");
			}
		
		}

	}

	return 0;

}


//命令解析
int 
yingxue_wifi_process_command(struct wifi_frame_tag *wifi_frame)
{




	uint8_t data_len = wifi_frame->data[1];
	uint32_t command = 0;
	//属性ID 2个字节
	uint16_t command_id = (wifi_frame->data[2] << 8) | (wifi_frame->data[3] & 0xff);

	//大于4个字节的长度错误
	if (data_len > 4){
		return -1;
	}

	for (int i = 0; i < data_len; i++){
		command = (wifi_frame->data[4] << 8 * 3) | (wifi_frame->data[5] << 8 * 2) | (wifi_frame->data[6] << 8) | wifi_frame->data[7];
	}


	//开关
	if (command_id == WIFI_CTR_OPEN){
		//关机
		if (command == 0){
			SEND_OPEN_CMD();
		}
		//开机
		else{
			SEND_OPEN_CMD();
		}
		
	}
	//选择模式0：常规模式1：果蔬模式2：ECO模式
	else if (command_id == WIFI_CTR_MODE){

		if (command == 0){
		
			yingxue_base.moshi_mode = 0;
		}
		else if (command == 1){
			yingxue_base.moshi_mode = 3;
		}
		else if (command == 2){
			yingxue_base.moshi_mode = 2;
		}

		
	}
	else if (command_id == WIFI_CTR_TEMP){

	}
	//无
	else if (command_id == WIFI_CTR_CHUSHUI){

	}
	//手动预约模式
	else if (command_id == WIFI_CTR_SHOUDONG){
		//无
		if (command == 0){

			yingxue_base.yure_mode = 0;
		}
		//单次循环
		else if (command == 1){
			yingxue_base.yure_mode = 1;
			get_rtc_time(&yingxue_base.yure_begtime, NULL);
			//2个小时 
			yingxue_base.yure_endtime.tv_sec = yingxue_base.yure_begtime.tv_sec + 60 * 60 * 2;
			SEND_OPEN_YURE_CMD();

		}
		//24小时循环
		else if (command == 2){
			yingxue_base.yure_mode = 2;
			SEND_OPEN_YURE_CMD();
		}


	}
	//设置回水温度

	else if (command_id == WIFI_CTR_HUISHUI){
		yingxue_base.huishui_temp = (uint8_t)command;
	
	}
	//无
	else if (command_id == WIFI_CTR_STATE){

	}
	//预热开关
	else if (command_id == WIFI_CTR_YUYUE_SW){
		if (yingxue_base.yure_mode == 3){
			yingxue_base.yure_mode = 0;
			memset(&yingxue_base.yure_endtime, 0, sizeof(struct timeval));
			//发送取消
			SEND_CLOSE_YURE_CMD();
		}
		else{
			yingxue_base.yure_mode = 3;
		}
	}
	else if (command_id == WIFI_CTR_YUTIME){
		for (int i = 0; i < 24; i++){
			if ((uint8_t)((command >> i) & 0x01) == 1){
			
				yingxue_base.dingshi_list[i] = 1;
			}
			else{
				yingxue_base.dingshi_list[i] = 0;
			}
		}
	}
	BACK_COMMAND_SUCCESS(command_id, 0x01);
}

//单片机回复数据
//@param cmd_state 命令
//@param state_id 状态ID
//@param data     上传状态下的数据
void yingxue_wifi_to_wifi(enum wifi_command_state cmd_state, uint8_t state_id, uint8_t data)
{
	struct wifi_uart_mq_tag wifi_uart_mq;
	//发送配网指令
	if (cmd_state == WIFI_CMD_EQUIP_UP){


		memmove(wifi_uart_mq.data, to_wifi_info, sizeof(to_wifi_info));
		wifi_uart_mq.len = sizeof(to_wifi_info);
	}
	else if (cmd_state == WIFI_CMD_NET){
		
		memmove(wifi_uart_mq.data, to_wifi_net, sizeof(to_wifi_net));
		wifi_uart_mq.len = sizeof(to_wifi_net);

	}
	else if (cmd_state == WIFI_CMD_STATE_UP){
		wifi_uart_mq.data[0] = 0xfc;
		wifi_uart_mq.data[1] = 0x00;
		wifi_uart_mq.data[2] = 0x08;
		wifi_uart_mq.data[3] = 0x05;
		wifi_uart_mq.data[4] = 0x00;
		wifi_uart_mq.data[5] = 0x04;

		//熟悉id
		for (int i = 0; i < 2; i++){
			wifi_uart_mq.data[6 + i] = (uint8_t)((state_id >> (8 * (1 - i))) & 0xff);
			
		}
		//数据
		for (int i = 0; i < 4; i++){
			wifi_uart_mq.data[8 + i] = (uint8_t)((state_id >> (8 * (3 - i))) & 0xff);
		}
		for (int i = 0; i < 12; i++){
			wifi_uart_mq.data[12] = (uint8_t)((wifi_uart_mq.data[12] + wifi_uart_mq.data[i]) & 0xff);
		}
		wifi_uart_mq.len = 13;

	}
	else if (cmd_state == WIFI_CMD_STATE_CTR){
		wifi_uart_mq.data[0] = 0xfc;
		wifi_uart_mq.data[1] = 0x00;
		wifi_uart_mq.data[2] = 0x03;
		wifi_uart_mq.data[3] = 0x07;
		//熟悉id
		for (int i = 0; i < 2; i++){
			wifi_uart_mq.data[4 + i] = (uint8_t)((state_id >> (8 * (1 - i))) & 0xff);

		}
		wifi_uart_mq.data[6] = 0x01;
		wifi_uart_mq.data[7] = 0x8;
		wifi_uart_mq.len = 8;
	}
	//fc 00 00 00 fc
	else if (cmd_state == WIFI_CMD_STATE_OK){
		wifi_uart_mq.data[0] = 0xfc;
		wifi_uart_mq.data[1] = 0x00;
		wifi_uart_mq.data[2] = 0x00;
		wifi_uart_mq.data[3] = 0x00;
		wifi_uart_mq.data[4] = 0xfc;
		wifi_uart_mq.len = 5;
	}
}