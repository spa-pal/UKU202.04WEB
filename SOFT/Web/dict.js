var set_dict = [
	["Общие установки","HEAD"," "," "," "," ",[ ]," ","s00"],
	["Серийный номер","Серийный номер изделия.","","INT","INTINPUT","DIAP",[10000,100000],"serno_____",0],	
	["Размещение","Название месторасположения устройства.","","STRING","STRINGINPUT","MAXLENGTH",50,"place_____",1],
	["Звуковой сигнал ИБЭП.","Включенность-выключенность звуковой сигнализации аварийных состояний ИБЭПа","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"zv_on_____",2],
	["Отключение сигнала авария.","Автоматическое снятие сигнализации аварийных ситуаций ИБЭПа при их пропадании.","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"av_avt____",4],
	["Мнемоника.","Задержка включения мнемонической диаграммы на дисплее УКУ('0' - выключить).","сек.","INTOFF","INTINPUT","DIAP",[5,300],"mnemo_____",5],

	["Структура","HEAD"," "," "," "," ",[ ]," ","s00"],
	/*["Фазность питающей сети","Количество фаз питающей сети","","ONOFF","RADIOINPUT","",["1 фаза","3 фазы"],"numphase_",60],*/
	["Выпрямители","Количество выпрямителей в структуре ИБЭП","","INT","INTINPUT","DIAP",[1,2],"numist_",59],
	["Сухие контакты","Количество сухих контактов в структуре ИБЭП","","INT","INTINPUT","DIAP",[0,4],"numsk_",61],
	["Дополнительные датчики температуры","Количество дополнительных датчиков в структуре ИБЭП","","INT","INTINPUT","DIAP",[0,3],"numdt_",62],
	/*["Блок дискретных вводов","Наличие или отсутствие в структуре ИБЭП блока дискретных логических входов","","ONOFF","RADIOINPUT","",["Нет","Есть"],"numenmv_",64],
	["Поэлементный мониторинг АКБ ","Наличие или отсутствие в структуре ИБЭП блока поэлементного контроля АКБ","","ONOFF","RADIOINPUT","",["Нет","Есть"],"nummakb_",63],*/

	["Выпрямители","HEAD"," "," "," "," ",[ ]," ","s00"],
	["Основной источник","Номер источника находящегося в постоянной работе","","INT","INTINPUT","DIAP",[1,2],"main_bps_",3],
	/*["Время ротации выпрямителей","Время ротации выпрямителей в часах, рабочие значения 1 ~ 500, 0 - выключено","ч.","INT","INTINPUT","DIAP",[0,500],"rot_t_____",7],*/
	["Imax.","Ток переключения на большее количество выпрямителей, дискретность 0.1А","A","INT/10","INTINPUT","DIAP",[10,1000],"i_max_____",8],
	["Imin.","Ток переключения на меньшее количество выпрямителей, дискретность 0.1А","A","INT/10","INTINPUT","DIAP",[10,1000],"i_min_____",9],
	["Umax","Аварийное напряжение выпрямителей максимальное, дискретность 0.1В","В","INT/10","INTINPUT","DIAP",[10,3000],"u_max_i_",10],
	/*["Umin","Аварийное напряжение выпрямителей минимальное, дискретность 0.1В","В","INT/10","INTINPUT","DIAP",[10,3000],"u_min_i_",11],*/
	["U0б","Напряжение поддержания при работе без АКБ , дискретность 0.1В","В","INT/10","INTINPUT","DIAP",[15,80],"u0b_",26],
	/*["tи.сигн","Сигнальная температура выпрямителей, дискретность 1°С","°С","INT","INTINPUT","DIAP",[10,100],"tsign_",20],*/
	["tи.max","Аварийная температура выпрямителей, дискретность 1°С","°С","INT","INTINPUT","DIAP",[10,100],"tmax_",21],
	["АПВ1","Включенность/выключенность АПВ первого уровня","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"apv1_on_",23],
	["АПВ2","Включенность/выключенность АПВ второго уровня","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"apv2_on_",24],
	["АПВ2период","Период работы АПВ второго уровня, дискретность 1ч.","ч.","INT","INTINPUT","DIAP",[1,24],"apv2_time_",25],

	["Сеть","HEAD"," "," "," "," ",[ ]," ","s00"],
	["Umin.сети","Минимальное рабочее напряжение питающей сети","","INT","INTINPUT","DIAP",[1,220],"un_min_",6],
	["Umax.сети","Максимальное рабочее напряжение питающей сети","","INT","INTINPUT","DIAP",[1,300],"un_max_",7],


	["Время","HEAD"," "," "," "," ",[ ]," ","s00"],	
	["Год","Установка текущего года","","INT","INTINPUT","DIAP",[1,99],"year_",29],
	["Месяц","Установка текущего месяца","","INT","INTINPUT","DIAP",[1,12],"month_",30],
	["День","Установка текущего дня","","INT","INTINPUT","DIAP",[1,31],"day_",31],
	["Час","Установка текущего часа","","INT","INTINPUT","DIAP",[0,23],"hour_",32],
	["Минуты","Установка текущих мигут","","INT","INTINPUT","DIAP",[0,59],"minut_",33],
	/*["Секунды","Установка секунд","","INT","INTINPUT","DIAP",[0,59],"secund_",34],*/
	["Часовой пояс","Установка часового пояса места расположения ИБЭПа для корректной работы процедуры синхронизации времени через интернет","","INT","INTINPUT","DIAP",[-12,12],"sntp_gmt_",56],
	["Синхронизация по SNTP","Включенность/период автоматической синхронизация времени и даты по серверу SNTP. Для правильного выполнения процедуры необходимо корректно установить часовой пояс","","STRING","EXECBUTTON","DIAP",[0,59],"sntp_exe_",34],
	["Источник синхронизации SNTP","Выбор источника синхронизации даты и времени - сервер SNTP 'ntp4.stratum2.ru' (IP адрес 88.147.254.230) либо сервер с IP указанным в настройках 'Адрес сервера SNTP'","","ONOFF","RADIOINPUT","",["'ntp4.stratum2.ru'","пользовательский сервер SNTP"],"sntp_src_",57],
	["Адрес сервера SNTP","IP адрес сервера SNTP, четыре тетрады через точку","","IP","IPINPUT","",[],"sntp_ip_",58],
	
	["Батареи","HEAD"," "," "," "," ",[ ]," ","s00"],
	["Uб20","Напряжение содержания АКБ при t = 20 °С, дискретность 0.1В","В","INT/10","INTINPUT","DIAP",[150,800],"ub20_",12],
	["Uб0","Напряжение содержания АКБ при t = 0 °С, дискретность 0.1В","В","INT/10","INTINPUT","DIAP",[150,800],"ub0_",13],
	["Uсигн","Напряжение сигнализирующее разряд АКБ, дискретность 1В","В","INT","INTINPUT","DIAP",[15,100],"usign_",14],
	["Iз.max","Максимальный ток заряда АКБ, дискретность 0.1А","А","INT/10","INTINPUT","DIAP",[1,150],"izmax_",15],
	["tбат.сигн","Сигнальная температура батареи, дискретность 1°С","°С","INT","INTINPUT","DIAP",[10,100],"tbatsign_",16],
	["tбат.max","Аварийная температура батареи, дискретность 1°С","°С","INT","INTINPUT","DIAP",[10,100],"tbatmax_",17],
	["Тз.а.с.","Время задержки включения БПС, дискретность 1 с.","с","INT","INTINPUT","DIAP",[0,10],"tzas_",22],
	["Tбат.","Время проверки цепи АКБ, дискретность 1 мин. (0 - выключено)","мин.","INT","INTINPUT","DIAP",[5,60],"tbat_",27],
	["Iбк.","Контрольный ток цепи батареи , дискретность 0.01А","А","INT/100","INTINPUT","DIAP",[1,500],"ikb_",28],
	["Uвыр.зар","Напряжение выравнивающего заряда, дискретность 0.1В","В","INT/10","INTINPUT","DIAP",[10,1000],"uvz_",18],
	["Tвыр.зар","Длительность выравнивающего заряда, дискретность 1ч.","ч.","INT","INTINPUT","DIAP",[1,24],"tvz_",19],
	["Автоматический выравнивающий заряд","Включенность/выключенность и период запуска автоматического выравнивающего заряда","","ONOFF","RADIOINPUT","",["ВЫКЛ.","1м.","2м.","3м.","6м.","12м."],"avzt_",35],
	
	["Внешние датчики","HEAD"," "," "," "," ",[ ]," ","s00"],
	["Сухой контакт №1, физическое состояние","Физическое состояние (замкнут/разомкнут) сухого контакта №1","","ONOFF","NOCONTROL","",["разомкнут","замкнут"],"",36],
	["Сухой контакт №1, аварийное состояние","Состояние сухого контакта №1 считающееся аварийным","","ONOFF","RADIOINPUT","",["разомкнут","замкнут"],"sk1avsign_",37],
	["Сухой контакт №1, отображение на экран УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №1 на экран УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk1lcden_",48],
	["Сухой контакт №1, звуковой сигнал УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №1 звуковым сигналом УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk1zven_",52],
	["Сухой контакт №2, физическое состояние","Физическое состояние (замкнут/разомкнут) сухого контакта №2","","ONOFF","NOCONTROL","",["разомкнут","замкнут"],"",39],
	["Сухой контакт №2, аварийное состояние","Состояние сухого контакта №2 считающееся аварийным","","ONOFF","RADIOINPUT","",["разомкнут","замкнут"],"sk2avsign_",40],
	["Сухой контакт №2, отображение на экран УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №2 на экран УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk2lcden_",49],
	["Сухой контакт №2, звуковой сигнал УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №2 звуковым сигналом УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk2zven_",53],
	["Сухой контакт №3, физическое состояние","Физическое состояние (замкнут/разомкнут) сухого контакта №3","","ONOFF","NOCONTROL","",["разомкнут","замкнут"],"",42],
	["Сухой контакт №3, аварийное состояние","Состояние сухого контакта №3 считающееся аварийным","","ONOFF","RADIOINPUT","",["разомкнут","замкнут"],"sk3avsign_",43],
	["Сухой контакт №3, отображение на экран УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №3 на экран УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk3lcden_",50],
	["Сухой контакт №3, звуковой сигнал УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №3 звуковым сигналом УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk3zven_",54],
	["Сухой контакт №4, физическое состояние","Физическое состояние (замкнут/разомкнут) сухого контакта №4","","ONOFF","NOCONTROL","",["разомкнут","замкнут"],"",45],
	["Сухой контакт №4, аварийное состояние","Состояние сухого контакта №4 считающееся аварийным","","ONOFF","RADIOINPUT","",["разомкнут","замкнут"],"sk4avsign_",46],
	["Сухой контакт №4, отображение на экран УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №4 на экран УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk4lcden_",51],
	["Сухой контакт №4, звуковой сигнал УКУ","Включенность/выключенность отображения аварийного статуса сухого контакта №4 звуковым сигналом УКУ","","ONOFF","RADIOINPUT","",["ВЫКЛ.","ВКЛ."],"sk4zven_",55]	
	/*,
	["Синхронизация","Контрольный ток цепи батареи , дискретность 0.01А","А","INT/100","INTINPUT","DIAP",[1,500],"sinhr_",35]*/
];
var bps_status_string = [
	"",
	"работает",
	"в резерве",
	"работает, сильный нагрев",
	"заблокирован извне",
	"работает АПВ",
	"АВАРИЯ!!! Перегрев",
	"АВАРИЯ!!! Занижено выходное напряжение",
	"АВАРИЯ!!! Завышено выходное напряжение",
	"АВАРИЯ!!! Потеряна связь",
	"Отсутствует первичное питание"
];

var alarm_status_string = [
	"",
	"Авария питающей сети!!!",
	["Авария батареи №","!!! Батарея не подключена."],
	["Авария батареи №","!!! Несимметрия."],
	"Несимметрия батареи",
	"",
];

function pad(a,b){return(1e15+a+"").slice(-b)};

console.log("dict.js загружен");