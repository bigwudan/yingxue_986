﻿#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scene.h"
#include "ctrlboard.h"
#include "ite/itu.h"
#include "ite/itp.h"


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
extern struct node_widget yureshijian_widget_num_0; //预热时间控制控件2
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

//樱雪基础数据
extern struct yingxue_base_tag yingxue_base;

//闪烁 0 不闪烁 1闪烁
unsigned  char is_shake;

//主页面初始化
static void MainLayer_init()
{
	ITUWidget *t_widget = NULL;
	//全部隐藏边框
	t_widget = ituSceneFindWidget(&theScene, "Background100");
	ituWidgetSetVisible(t_widget, false);
	t_widget = ituSceneFindWidget(&theScene, "Background102");
	ituWidgetSetVisible(t_widget, false);
	t_widget = ituSceneFindWidget(&theScene, "Background134");
	ituWidgetSetVisible(t_widget, false);
	//默认选中中间一个边框
	curr_node_widget = &mainlayer_1;
	t_widget = ituSceneFindWidget(&theScene, curr_node_widget->focus_back_name);
	ituWidgetSetVisible(t_widget, true);
	//初始化状态
	yingxue_base.adjust_temp_state = 0;
	is_shake = 0;

	//预热模式 0 预热 1单巡航 2全天候巡航 3下次预热时间
	t_widget = ituSceneFindWidget(&theScene, "yureSprite");

	if (yingxue_base.yure_mode == 0){
		ituSpriteGoto(t_widget, 0);
	}
	else if (yingxue_base.yure_mode == 1){
		ituSpriteGoto(t_widget, 1);
	}
	else if (yingxue_base.yure_mode == 2){
		ituSpriteGoto(t_widget, 2);
	}
	else if (yingxue_base.yure_mode == 3){
		int beg = 0;
		int end = 0;
		char t_buf[100] = { 0 };
		//计算下次预热时间
		calcNextYure(&beg, &end);
		if (end == 0) end = beg;
		sprintf(t_buf, "%d:00--%d:59", beg, end);
		ituTextSetString(ituSceneFindWidget(&theScene, "Text35"), t_buf);
		ituSpriteGoto(t_widget, 3);

	}

}

//预热进入初始化
static void yureLayer()
{
	ITUWidget *t_widget = NULL;
	//全部隐藏
	t_widget = ituSceneFindWidget(&theScene, "BackgroundButton78");
	ituWidgetSetVisible(t_widget, false);
	t_widget = ituSceneFindWidget(&theScene, "Background27");
	ituWidgetSetVisible(t_widget, false);
	t_widget = ituSceneFindWidget(&theScene, "Background30");
	ituWidgetSetVisible(t_widget, false);
	t_widget = ituSceneFindWidget(&theScene, "Background46");
	ituWidgetSetVisible(t_widget, false);
	t_widget = ituSceneFindWidget(&theScene, "Background132");
	ituWidgetSetVisible(t_widget, false);
	//第三个大框中的小框
	t_widget = ituSceneFindWidget(&theScene, "Background94");
	ituWidgetSetVisible(t_widget, false);
	//默认选中第一个
	curr_node_widget = &yureLayer_0;
	t_widget = ituSceneFindWidget(&theScene, curr_node_widget->focus_back_name);
	ituWidgetSetVisible(t_widget, true);
	t_widget = ituSceneFindWidget(&theScene, curr_node_widget->name);
	ituWidgetSetVisible(t_widget, false);


	//预热时间
	int beg = 0;
	int end = 0;
	char t_buf[100] = { 0 };
	//计算下次预热时间
	calcNextYure(&beg, &end);
	if (end == 0) end = beg;
	sprintf(t_buf, "%02d--%02d", beg, end);
	t_widget = ituSceneFindWidget(&theScene, "Text99");
	ituTextSetString(t_widget, t_buf);
}

//预热时间设置
static void yureshijianLayer()
{
	//初始化 屏蔽所有的显示
	ITUWidget *t_widget = NULL;
	curr_node_widget = &yureshijian_widget_0;
	//默认选中第一个
	t_widget = ituSceneFindWidget(&theScene, curr_node_widget->focus_back_name);
	ituWidgetSetVisible(t_widget, true);
	t_widget = ituSceneFindWidget(&theScene, curr_node_widget->name);
	ituWidgetSetVisible(t_widget, false);

}

//预热设置温度和北京时间
static void yureshezhiLayer()
{
	ITUWidget *t_widget = NULL;
	char t_buf[10] = { 0 };
	//默认选中第一个
	curr_node_widget = &yureshezhiLayer_0;
	//没有选中
	t_widget = ituSceneFindWidget(&theScene, "BackgroundButton60");
	ituWidgetSetVisible(t_widget, false);

	//焦点在
	t_widget = ituSceneFindWidget(&theScene, "BackgroundButton85");
	ituWidgetSetVisible(t_widget, true);



	//Background37
	//焦点选框
	t_widget = ituSceneFindWidget(&theScene, "Background37");
	ituWidgetSetVisible(t_widget, false);

	//选中背景
	t_widget = ituSceneFindWidget(&theScene, "Background45");
	ituWidgetSetVisible(t_widget, false);
	//Background33
	//焦点选框
	t_widget = ituSceneFindWidget(&theScene, "Background33");
	ituWidgetSetVisible(t_widget, false);

	//选中背景Background105
	t_widget = ituSceneFindWidget(&theScene, "Background105");
	ituWidgetSetVisible(t_widget, false);


	//Background4
	//焦点
	t_widget = ituSceneFindWidget(&theScene, "Background40");
	ituWidgetSetVisible(t_widget, false);

	//选中背景
	t_widget = ituSceneFindWidget(&theScene, "Background107");
	ituWidgetSetVisible(t_widget, false);

	//设置时间
	struct timeval curr_time;
	struct tm *t_tm;
	get_rtc_time(&curr_time, NULL);
	t_tm = localtime(&curr_time);

	//设置小时
	t_widget = ituSceneFindWidget(&theScene, "Text42");
	sprintf(t_buf, "%02d", t_tm->tm_hour);
	ituTextSetString(t_widget, t_buf);

	//设置min
	t_widget = ituSceneFindWidget(&theScene, "Text43");
	sprintf(t_buf, "%02d", t_tm->tm_min);
	ituTextSetString(t_widget, t_buf);
}

//设置模式
static void moshiLayer()
{
	//默认选中第一个
	curr_node_widget = &moshiLayer_0;
	ITUWidget *t_widget = NULL;

	//显示所有
	t_widget = ituSceneFindWidget(&theScene, "BackgroundButton33");
	ituWidgetSetVisible(t_widget, true);
	//1
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton10");
	ituWidgetSetVisible(t_widget, true);

	//2
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton11");
	ituWidgetSetVisible(t_widget, true);

	//3
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton12");
	ituWidgetSetVisible(t_widget, true);

	//4
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton13");
	ituWidgetSetVisible(t_widget, true);



	t_widget = ituSceneFindWidget(&theScene, "BackgroundButton68");
	ituWidgetSetVisible(t_widget, false);
	//1
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton80");
	ituWidgetSetVisible(t_widget, false);

	//2
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton79");
	ituWidgetSetVisible(t_widget, false);

	//3
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton81");
	ituWidgetSetVisible(t_widget, false);

	//4
	t_widget = ituSceneFindWidget(&theScene, "moshi_BackgroundButton82");
	ituWidgetSetVisible(t_widget, false);

}

//设置模式
static void chushui()
{
	ITUWidget *t_widget = NULL;
	char t_buf[10] = { 0 };
	//默认第一个
	curr_node_widget = &chushui_0;

	t_widget = ituSceneFindWidget(&theScene, "chushui_BackgroundButton7");
	ituWidgetSetVisible(t_widget, true);
	//1
	t_widget = ituSceneFindWidget(&theScene, "chushui_BackgroundButton73");
	ituWidgetSetVisible(t_widget, false);


	//根据设置温度显示Text38
	t_widget = ituSceneFindWidget(&theScene, "Text38");
	if (yingxue_base.select_set_moshi_mode > 0){
		if (yingxue_base.select_set_moshi_mode == 1){
			sprintf(t_buf, "%02d", yingxue_base.normal_moshi.temp);
			ituTextSetString(t_widget, t_buf);
		}
		else if (yingxue_base.select_set_moshi_mode == 2){
			sprintf(t_buf, "%02d", yingxue_base.super_moshi.temp);
			ituTextSetString(t_widget, t_buf);
		}
		else if (yingxue_base.select_set_moshi_mode == 3){
			sprintf(t_buf, "%02d", yingxue_base.eco_moshi.temp);
			ituTextSetString(t_widget, t_buf);
		}
		else if (yingxue_base.select_set_moshi_mode == 4){
			sprintf(t_buf, "%02d", yingxue_base.fruit_moshi.temp);
			ituTextSetString(t_widget, t_buf);
		}
	}

	//选中背景
	t_widget = ituSceneFindWidget(&theScene, "chushui_Background45");
	ituWidgetSetVisible(t_widget, false);
	//焦点
	t_widget = ituSceneFindWidget(&theScene, "chushui_Background37");
	ituWidgetSetVisible(t_widget, false);

	//确定按键
	t_widget = ituSceneFindWidget(&theScene, "chushui_Background51");
	ituWidgetSetVisible(t_widget, false);
}

//樱雪每个页面初始化
bool YX_MenuOnEnter(ITUWidget* widget, char* param)
{
	static int test_flag = 0;
	ITUWidget *t_widget = NULL;
	char t_buf[10] = { 0 };

	//welcome页面
	if (strcmp(widget->name, "welcom") == 0){

	}
	//MainLayer 首页
	else if (strcmp(widget->name, "MainLayer") == 0){
		MainLayer_init();
	}
	//预热页面
	else if (strcmp(widget->name, "yureLayer") == 0){
		yureLayer();
	}
	//预热时间设置
	else if (strcmp(widget->name, "yureshijianLayer") == 0){
		yureshijianLayer();
	}
	//预热设置 温度，北京时间yureshezhiLayer
	else if (strcmp(widget->name, "yureshezhiLayer") == 0){
		yureshezhiLayer();
	}
	else if (strcmp(widget->name, "moshiLayer") == 0){
		moshiLayer();
	}
	//chushui
	else if (strcmp(widget->name, "chushui") == 0){
		chushui();
	}
	return true;

}

//樱雪主页面定时任务
bool MainLayerOnTimer(ITUWidget* widget, char* param)
{
	//1秒运行一次
	static struct timeval last_tm;
	//闪烁的时间
	static struct timeval during_tm;
	struct timeval now_tm;
	char t_buf[20] = { 0 };
	ITUWidget* t_widget;
	get_rtc_time(&now_tm, NULL);
	if (now_tm.tv_sec < last_tm.tv_sec + 1){
		return true;
	}

	//如何闪烁
	if (is_shake == 1){
		//得到当前时间
		if (yingxue_base.adjust_temp_state == 1){
			get_rtc_time(&during_tm, NULL);
		}
		//开始闪烁
		yingxue_base.adjust_temp_state = 2;
		t_widget = (ITUWidget*)ituSceneFindWidget(&theScene, "Text17");
		//大于7秒，闪烁结束
		if (now_tm.tv_sec > during_tm.tv_sec + 5){
			yingxue_base.adjust_temp_state = 0;
			if (t_widget->visible == 0){
				ituWidgetSetVisible(t_widget, true);
			}
			//时间归零
			memset(&during_tm, 0, sizeof(struct timeval));
		}
		else{
			if (t_widget){
				if (t_widget->visible == 0){
					ituWidgetSetVisible(t_widget, true);
				}
				else{
					ituWidgetSetVisible(t_widget, false);
				}
			}
		}
	}
	else{
		if (yingxue_base.adjust_temp_state == 0 || yingxue_base.adjust_temp_state == 3){
			//显示出水温度
			sprintf(t_buf, "%d", yingxue_base.chushui_temp);
			t_widget = ituSceneFindWidget(&theScene, "Text17");
			ituTextSetString(t_widget, t_buf);

			//Background34
			if (yingxue_base.state_show & 0x01){
				//显示
				t_widget = ituSceneFindWidget(&theScene, "Background34");
				ituWidgetSetVisible(t_widget, true);

			}
			else{
				//不显示
				t_widget = ituSceneFindWidget(&theScene, "Background34");
				ituWidgetSetVisible(t_widget, false);
			}

			//Background35
			if (yingxue_base.state_show & 0x04){
				//显示
				t_widget = ituSceneFindWidget(&theScene, "Background35");
				ituWidgetSetVisible(t_widget, true);

			}
			else{
				//不显示
				t_widget = ituSceneFindWidget(&theScene, "Background35");
				ituWidgetSetVisible(t_widget, false);
			}

			//Background36
			if (yingxue_base.state_show & 0x02){
				//显示
				t_widget = ituSceneFindWidget(&theScene, "Background36");
				ituWidgetSetVisible(t_widget, true);

			}
			else{
				//不显示
				t_widget = ituSceneFindWidget(&theScene, "Background36");
				ituWidgetSetVisible(t_widget, false);
			}

		}
	}
	get_rtc_time(&last_tm, NULL);
	return true;
}

//开机画面定时器
bool WelcomeOnTimer(ITUWidget* widget, char* param)
{

	//是否已经动作
	static unsigned char flag;
	//第一次上电
	if (yingxue_base.run_state == 0){
		sleep(2);
		//开机
		SEND_OPEN_CMD();
		yingxue_base.run_state = 1;
		ituLayerGoto(ituSceneFindWidget(&theScene, "MainLayer"));

	}
	//关机
	else if (yingxue_base.run_state == 2){
		if (flag != 2){
			sleep(2);
			//关机
			SEND_CLOSE_CMD();
			ioctl(ITP_DEVICE_BACKLIGHT, ITP_IOCTL_OFF, NULL);
			flag = 2;
		}
	}//开机
	else if (yingxue_base.run_state == 1){
		if (flag != 1){
			ioctl(ITP_DEVICE_BACKLIGHT, ITP_IOCTL_ON, NULL);
			//开机
			SEND_OPEN_CMD();
			sleep(2);
			ituLayerGoto(ituSceneFindWidget(&theScene, "MainLayer"));
		}
	}
	return true;
}

//ERROnTimer
bool ERROnTimer(ITUWidget* widget, char* param)
{
	sleep(2);
	if (yingxue_base.is_err == 0){
		ituLayerGoto(ituSceneFindWidget(&theScene, "MainLayer"));
	}
	return true;
}

void MainMenuReset(void)
{
	return;
}
