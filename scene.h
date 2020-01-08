﻿/** @file
 * ITE Display Control Board Scene Definition.
 *
 * @author Jim Tan
 * @version 1.0
 * @date 2015
 * @copyright ITE Tech. Inc. All Rights Reserved.
 */
/** @defgroup ctrlboard ITE Display Control Board Modules
 *  @{
 */
#ifndef SCENE_H
#define SCENE_H

#include "ite/itu.h"
#include "ctrlboard.h"
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ctrlboard_scene Scene
 *  @{
 */

#define MS_PER_FRAME                17              ///< Drawing delay per frame

typedef enum
{
	EVENT_CUSTOM_SCREENSAVER = ITU_EVENT_CUSTOM,    ///< Ready to enter screensaver mode. Custom0 event on GUI Designer.
    EVENT_CUSTOM_SD_INSERTED,                       ///< #1: SD card inserted.
    EVENT_CUSTOM_SD_REMOVED,                        ///< #2: SD card removed.
	EVENT_CUSTOM_USB_INSERTED,                      ///< #3: USB drive inserted.
    EVENT_CUSTOM_USB_REMOVED,                       ///< #4: USB drive removed.
    EVENT_CUSTOM_KEY0,                              ///< #5: Key #0 pressed.
    EVENT_CUSTOM_KEY1,                              ///< #6: Key #1 pressed.
	EVENT_CUSTOM_KEY2,                              ///< #7: Key #2 pressed.
    EVENT_CUSTOM_KEY3,                              ///< #8: Key #3 pressed.
    EVENT_CUSTOM_UART                               ///< #9: UART message.

} CustomEvent;

// scene
/**
 * Initializes scene module.
 */
void SceneInit(void);

/**
 * Exits scene module.
 */
void SceneExit(void);

/**
 * Loads ITU file.
 */
void SceneLoad(void);

/**
 * Runs the main loop to receive events, update and draw scene.
 *
 * @return The QuitValue.
 */
int SceneRun(void);

/**
 * Gotos main menu layer.
 */
void SceneGotoMainMenu(void);

/**
 * Sets the status of scene.
 *
 * @param ready true for ready, false for not ready yet.
 */
void SceneSetReady(bool ready);

/**
 * Quits the scene.
 *
 * @param value The reason to quit the scene.
 */
void SceneQuit(QuitValue value);

/**
 * Gets the current quit value.
 *
 * @return The current quit value.
 */
QuitValue SceneGetQuitValue(void);

void SceneEnterVideoState(int timePerFrm);
void SceneLeaveVideoState(void);

/**
 * Changes language file.
 */
void SceneChangeLanguage(void);

/**
 * Predraw scene.
 *
 * @param arg Unused.
 */
void ScenePredraw(int arg);

/**
 * Global instance variable of scene.
 */
extern ITUScene theScene;

/** @} */ // end of ctrlboard_scene


//樱雪
//消息
//控制键回调函数
typedef void(*node_widget_cb)(struct node_widget *widget, unsigned char state);

//主页串口改变显示
struct main_uart_chg
{
	//第0位 有水  第1位 风机 第2位 火焰 第3位 风压
	unsigned char state_show;
	//设置温度
	unsigned char shezhi_temp;
	//出水温度
	unsigned char chushui_temp;
	//进水温度
	unsigned char jinshui_temp;
	//错误代码
	unsigned char err_no;
	//主机状态 0关机 1待机 2正常燃烧 3
	unsigned char machine_state;
	//是否故障
	unsigned char is_err;

};

//控制板回复数据结构
struct operate_data
{
	unsigned char data_0;

	//固定信息
	unsigned char data_1;
	unsigned char data_2;

	//回复数据
	unsigned char data_3;
	unsigned char data_4;
	unsigned char data_5;

	unsigned char data_6;
	unsigned char data_7;
	unsigned char data_8;
	//crc
	unsigned char data_9;
	unsigned char data_10;


};

//控制板回复数据结构
struct main_data
{
	//数据
	unsigned char data[17];
	//state 0开始
	unsigned char state;

};


//控制控件
struct node_widget
{
	unsigned char value;
	struct node_widget *up; //上一个控件
	struct node_widget *down; //下一个控件
	char *name; //控件名称
	char *focus_back_name; //选中控件背景
	char *checked_back_name; //确定控件背景
	uint8_t state; //状态0焦点 1锁定
	uint8_t type; //类型 0 普通 1可以锁定 2长按
	node_widget_cb updown_cb; //点击向上回调
	node_widget_cb confirm_cb; //确认回调
	node_widget_cb long_press_cb; //长按
};

//当前选中的空间
extern struct node_widget *curr_node_widget;

//主界面
extern struct node_widget mainlayer_0;
extern struct node_widget mainlayer_1;
extern struct node_widget mainlayer_2;

//预热界面
extern struct node_widget yureLayer_0;
extern struct node_widget yureLayer_1;
extern struct node_widget yureLayer_2;
extern struct node_widget yureLayer_3;
extern struct node_widget yureLayer_4;
extern struct node_widget yureLayer_5;



//预热时间页面
extern struct node_widget yureshijian_widget_0; //预热时间控制控件1
extern struct node_widget yureshijian_widget_num_1; //预热时间控制控件2
extern struct node_widget yureshijian_widget_num_2; //预热时间控制控件3
extern struct node_widget yureshijian_widget_num_3; //预热时间控制控件4
extern struct node_widget yureshijian_widget_num_4; //预热时间控制控件5
extern struct node_widget yureshijian_widget_num_5; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_6; //预热时间控制控件2
extern struct node_widget yureshijian_widget_num_7; //预热时间控制控件3
extern struct node_widget yureshijian_widget_num_8; //预热时间控制控件4
extern struct node_widget yureshijian_widget_num_9; //预热时间控制控件5
extern struct node_widget yureshijian_widget_num_10; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_11; //预热时间控制控件2
extern struct node_widget yureshijian_widget_num_12; //预热时间控制控件3
extern struct node_widget yureshijian_widget_num_13; //预热时间控制控件4
extern struct node_widget yureshijian_widget_num_14; //预热时间控制控件5
extern struct node_widget yureshijian_widget_num_15; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_16; //预热时间控制控件2
extern struct node_widget yureshijian_widget_num_17; //预热时间控制控件3
extern struct node_widget yureshijian_widget_num_18; //预热时间控制控件4
extern struct node_widget yureshijian_widget_num_19; //预热时间控制控件5
extern struct node_widget yureshijian_widget_num_20; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_21; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_22; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_23; //预热时间控制控件6
extern struct node_widget yureshijian_widget_num_24; //预热时间控制控件6

//预约时间
extern struct node_widget yureshezhiLayer_0;
extern struct node_widget yureshezhiLayer_1;
extern struct node_widget yureshezhiLayer_2;
extern struct node_widget yureshezhiLayer_3;

//模式
extern struct node_widget moshiLayer_0;
extern struct node_widget moshiLayer_1;
extern struct node_widget moshiLayer_2;
extern struct node_widget moshiLayer_3;
extern struct node_widget moshiLayer_4;

//出水模式
extern struct node_widget chushui_0;
extern struct node_widget chushui_1;
extern struct node_widget chushui_2;

//模式
struct moshi_data{
	unsigned char temp;
};

//樱雪基础数据
struct yingxue_base_tag{
	//预热
	struct node_widget *yure_time_widget; //预热时间
	unsigned char yure_mode; //预热模式 0无模式 1单巡航模式 2 全天候模式 3 预约模式
	struct timeval yure_begtime; //预热开始时间
	struct timeval yure_endtime; //预热结束时间
	unsigned char yure_set_count; //预热设置开始时间
	unsigned char huishui_temp; //回水温度

	//moshi
	unsigned char moshi_mode; // 模式 0无模式 1 普通模式 2 超级模式 3 节能模式 4 水果模式
	unsigned char select_set_moshi_mode;// 选择设置模式 0无模式 1 普通模式 2 超级模式 3 节能模式 4 水果模式
	struct moshi_data normal_moshi; //普通模式
	struct moshi_data super_moshi; //超级模式
	struct moshi_data eco_moshi; //节能模式
	struct moshi_data fruit_moshi; //水果模式
};

//发送串口命令
void send_uart_cmd(struct operate_data *var_opt_data);

//接受主板来的命令 0成功 1未完成 -1失败
char recv_uart_cmd();



extern struct yingxue_base_tag yingxue_base;

//串口的数据
struct uart_data_tag{
	unsigned char count;//当前数据数
	unsigned char buf_data[20]; //当前缓存
	unsigned char state; //状态  0正常 1错误 2已经完成
};
#define MAX_CHAIN_NUM 50
//环形队列
struct chain_list_tag{
	unsigned char rear; //尾结点
	unsigned char front; //头结点
	unsigned char count; //当前数量
	unsigned char buf[MAX_CHAIN_NUM];
};

//分析得到的数组
void process_frame(struct main_uart_chg *dst, const unsigned char *src);


#ifdef __cplusplus
}
#endif

#endif /* SCENE_H */
/** @} */ // end of ctrlboard