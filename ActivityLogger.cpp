/*
 */

//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "ActivityLogger.h"
#include "ActivityLoggerPlugCallback.h"




struct LoggerInfo {
	t_logger_func_array func_array;
	void* privateLoggerPtr;
} ;


struct List_LoggerInfo {
	LoggerInfo lgi;
	List_LoggerInfo* next;
} ;


struct List_LoggerInfo* p_logger_info_list;



UNITEX_FUNC int UNITEX_CALL AddLoggerInfo(const t_logger_func_array* func_array,void* privateLoggerPtr)
{
	struct List_LoggerInfo* new_item;
	new_item = (struct List_LoggerInfo*)malloc(sizeof(struct List_LoggerInfo));
	if (new_item == NULL)
		return 0;

	new_item->lgi.func_array = *func_array;
	new_item->lgi.privateLoggerPtr = privateLoggerPtr;
	new_item->next = NULL;

	if (p_logger_info_list == NULL)
		p_logger_info_list = new_item;
	else {
		struct List_LoggerInfo* tmp = p_logger_info_list;
		while ((tmp->next) != NULL)
			tmp = tmp->next;
		tmp->next = new_item;
	}

	if ((new_item->lgi.func_array.fnc_Init_Logger) != NULL)
		(*(new_item->lgi.func_array.fnc_Init_Logger))(new_item->lgi.privateLoggerPtr);

	return 1;
}

UNITEX_FUNC int UNITEX_CALL RemoveLoggerInfo(const t_logger_func_array* func_array,void* privateLoggerPtr)
{
	struct List_LoggerInfo* tmp = p_logger_info_list;
	struct List_LoggerInfo* tmp_previous = NULL;

	while (tmp != NULL)
	{
		if ((memcmp(&tmp->lgi.func_array,func_array,sizeof(t_logger_func_array))==0) &&
			(tmp->lgi.privateLoggerPtr == privateLoggerPtr))
		{
			if (tmp_previous == NULL)
				p_logger_info_list = tmp->next;
			else
				tmp_previous->next = tmp->next;

			if ((tmp->lgi.func_array.fnc_Uninit_Logger) != NULL)
				(*(tmp->lgi.func_array.fnc_Uninit_Logger))(tmp->lgi.privateLoggerPtr);

			free(tmp);
			return 1;
		}
		tmp_previous = tmp;
		tmp = tmp->next;
	}
	return 0;
}


UNITEX_FUNC int UNITEX_CALL GetNbLoggerInfoInstalled()
{
    int count=0;
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        count++;
		tmp = tmp->next;
	}
	return count;
}



void Call_logger_fnc_before_af_fopen(const char* name,const char* MODE)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_before_af_fopen) != NULL)
            (*(tmp->lgi.func_array.fnc_before_af_fopen))(name,MODE,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_after_af_fopen(const char* name,const char* MODE,ABSTRACTFILE* af)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_after_af_fopen) != NULL)
            (*(tmp->lgi.func_array.fnc_after_af_fopen))(name,MODE,af,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_before_af_fclose(ABSTRACTFILE* af)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_before_af_fclose) != NULL)
            (*(tmp->lgi.func_array.fnc_before_af_fclose))(af,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_after_af_fclose(ABSTRACTFILE* af,int ret)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_after_af_fclose) != NULL)
            (*(tmp->lgi.func_array.fnc_after_af_fclose))(af,ret,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_before_af_rename(const char* name1,const char* name2)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_before_af_rename) != NULL)
            (*(tmp->lgi.func_array.fnc_before_af_rename))(name1,name2,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_after_af_rename(const char* name1,const char* name2,int ret)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_after_af_rename) != NULL)
            (*(tmp->lgi.func_array.fnc_after_af_rename))(name1,name2,ret,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_before_af_copy(const char* name1,const char* name2)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_before_af_copy) != NULL)
            (*(tmp->lgi.func_array.fnc_before_af_copy))(name1,name2,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_after_af_copy(const char* name1,const char* name2,int ret)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_after_af_copy) != NULL)
            (*(tmp->lgi.func_array.fnc_after_af_copy))(name1,name2,ret,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}


void Call_logger_fnc_before_af_remove(const char* name)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_before_af_remove) != NULL)
            (*(tmp->lgi.func_array.fnc_before_af_remove))(name,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_after_af_remove(const char* name,int ret)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_after_af_remove) != NULL)
            (*(tmp->lgi.func_array.fnc_after_af_remove))(name,ret,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}


void Call_logger_fnc_before_calling_tool(mainFunc* fnc,int argc,char* argv[])
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_before_calling_tool) != NULL)
            (*(tmp->lgi.func_array.fnc_before_calling_tool))(fnc,argc,argv,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_after_calling_tool(mainFunc* fnc,int argc,char* argv[],int ret)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_after_af_remove) != NULL)
            (*(tmp->lgi.func_array.fnc_after_calling_tool))(fnc,argc,argv,ret,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_LogOutWrite(const void*Buf, size_t size)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_LogOutWrite) != NULL)
            (*(tmp->lgi.func_array.fnc_LogOutWrite))(Buf,size,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}

void Call_logger_fnc_LogErrWrite(const void*Buf, size_t size)
{
    struct List_LoggerInfo* tmp = p_logger_info_list;
	while (tmp != NULL)
	{
        if ((tmp->lgi.func_array.fnc_LogErrWrite) != NULL)
            (*(tmp->lgi.func_array.fnc_LogErrWrite))(Buf,size,tmp->lgi.privateLoggerPtr);
		tmp = tmp->next;
	}
}
