//=====================================================================
//鏂囦欢鍚嶇О锛歴pi.h
//鍔熻兘姒傝锛歴pi搴曞眰椹卞姩鏋勪欢婧愭枃�?
//鍒朵綔鍗曚綅锛氳嫃宸炲ぇ瀛﹀祵鍏ュ紡绯荤粺涓庣墿鑱旂綉鐮旂┒鎵�(sumcu.suda.edu.cn)
//�?   鏈�? 2019-05-09  V2.0
//閫傜敤鑺墖锛欿L25銆並L26銆並L36
//=====================================================================
#ifndef _SPI_H             //闃叉閲嶅瀹氫箟锛?寮��?
#define _SPI_H

#include "mcu.h"
#include "string.h"

#define SPI_1  0
#define SPI_2  1
#define SPI_3  2

#define SPI_MASTER  1
#define SPI_SLAVE  0
//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_init�?
//鍔熻兘璇存槑锛歋PI鍒濆鍖?
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿锛屽彲鐢ㄥ弬鏁板彲鍙傝gec.h鏂囦�?
//       MSTR锛歋PI涓讳粠鏈洪�夋嫨�?閫夋嫨涓轰粠�?1閫夋嫨涓轰富鏈恒�?
//       BaudRate锛氭尝鐗圭巼锛屽彲鍙?2000�?000�?000�?000�?500�?000锛屽崟浣嶏細b/s
//       CPOL锛欳POL=0锛氶珮鏈夋晥SPI鏃堕挓锛堜綆鏃犳晥锛夛紱CPOL=1锛氫綆鏈夋晥SPI鏃堕挓锛堥珮鏃犳晥锛?
//       CPHA锛欳PHA=0鐩镐綅涓?�?CPHA=1鐩镐綅涓?�?
//鍑芥暟杩斿洖锛氭�?
//鍑芥暟澶囨敞�?CPHA=0锛屾椂閽熶俊鍙风殑绗竴涓竟娌垮嚭鐜板�?鍛ㄦ湡鏁版嵁浼犺緭鐨勭涓�涓懆鏈熺殑涓ぎ锛?
//        CPHA=1锛屾椂閽熶俊鍙风殑绗竴涓竟娌垮嚭鐜板�?鍛ㄦ湡鏁版嵁浼犺緭鐨勭涓�涓懆鏈熺殑璧风偣銆?
//        CPHA=0鏃讹紝閫氫俊鏈�绋冲畾锛屽嵆鎺ユ敹鏂瑰湪1/2鍛ㄦ湡鐨勬椂鍒讳粠绾夸笂鍙栨暟銆?
//=====================================================================
void spi_init(uint8_t No,uint8_t MSTR,uint16_t BaudRate,uint8_t CPOL,uint8_t CPHA);

//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_send1.
//鍔熻兘璇存槑锛歋PI鍙戦�佷竴瀛楄妭鏁版嵁�?
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿銆?鍙敤鍙傛暟鍙弬瑙乬ec.h鏂囦�?
//       data�?    闇�瑕佸彂閫佺殑涓�瀛楄妭鏁版嵁�?
//鍑芥暟杩斿洖�?锛氬彂閫佸け璐ワ�?锛氬彂閫佹垚鍔熴�?
//=====================================================================
uint8_t spi_send1(uint8_t No,uint8_t data);

//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_sendN.
//鍔熻兘璇存槑锛歋PI鍙戦�佹暟鎹�?
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿銆?鍏跺彇鍊间负0�?
//       n:     瑕佸彂閫佺殑瀛楄妭涓暟銆傝寖鍥翠负(1~255)
//       data[]:鎵�鍙戞暟缁勭殑棣栧湴鍧�銆?
//鍑芥暟杩斿洖锛氭棤銆?
//=====================================================================
uint8_t spi_sendN(uint8_t No,uint8_t n,uint8_t data[]);

//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_receive1.
//鍔熻兘璇存槑锛歋PI鎺ユ敹涓�涓瓧鑺傜殑鏁版嵁
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿锛屽彲鐢ㄥ弬鏁板彲鍙傝gec.h鏂囦�?
//鍑芥暟杩斿洖锛氭帴鏀跺埌鐨勬暟鎹�?
//=====================================================================
uint8_t spi_receive1(uint8_t No);

//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_receiveN.
//鍔熻兘璇存槑锛歋PI鎺ユ敹鏁版嵁銆傚綋n=1鏃讹紝灏辨槸鎺ュ彈涓�涓瓧鑺傜殑鏁版嵁鈥︹�?
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿锛屽彲鐢ㄥ弬鏁板彲鍙傝gec.h鏂囦�?
//          n:    瑕佸彂閫佺殑瀛楄妭涓暟銆傝寖鍥翠负(1~255),
//       data[]:鎺ユ敹鍒扮殑鏁版嵁瀛樻斁鐨勯鍦板潃銆?
//鍑芥暟杩斿洖�?锛氭帴鏀舵垚�?鍏朵粬鎯呭喌锛氬け璐ャ�?
//=====================================================================
uint8_t spi_receiveN(uint8_t No,uint8_t n,uint8_t data[]);

//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_enable_re_int
//鍔熻兘璇存槑锛氭墦寮�SPI鎺ユ敹涓柇�?
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿锛屽彲鐢ㄥ弬鏁板彲鍙傝gec.h鏂囦�?
//鍑芥暟杩斿洖锛氭棤銆?
//=====================================================================
void spi_enable_re_int(uint8_t No);

//=====================================================================
//鍑芥暟鍚嶇О锛歴pi_disable_re_int
//鍔熻兘璇存槑锛氬叧闂璖PI鎺ユ敹涓柇�?
//鍑芥暟鍙傛暟锛歂o锛氭ā鍧楀彿锛屽彲鐢ㄥ弬鏁板彲鍙傝gec.h鏂囦�?
//鍑芥暟杩斿洖锛氭棤銆?
//=====================================================================
void spi_disable_re_int(uint8_t No);

#endif   //闃叉閲嶅瀹氫箟锛?缁撳�?

//=====================================================================
//澹版槑锛?
//�?锛夋垜浠紑鍙戠殑婧愪唬鐮侊紝鍦ㄦ湰涓績鎻愪緵鐨勭‖浠剁郴缁熸祴璇曢�氳繃锛岀湡璇氬鐚粰绀句細锛屼笉瓒充箣澶勶�?
//     娆㈣繋鎸囨�?
//�?锛夊浜庝娇鐢ㄩ潪鏈腑蹇冪‖浠剁郴缁熺殑鐢ㄦ埛锛岀Щ妞嶄唬鐮佹椂锛岃浠旂粏鏍规嵁鑷繁鐨勭‖浠跺尮閰嶃�?
//
//鑻忓窞澶уNXP宓屽叆寮忎腑�?http://sumcu.suda.edu.cn,0512-65214835)
