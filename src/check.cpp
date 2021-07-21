#include "check.hpp"
#include "redis.hpp"

bool check_packet(Packet *pkt) {
  // tagチェック
  int action;

  if (!pkt->get_tag()) { // pacektにタグがついていない場合
    // tagテーブルに問い合わせて、tagをつける
    std::string tag;
    tag = select_string(pkt->to_five_tuple().to_string());
    pkt->attach_tag(tag);
  }

  // tagを元に、actionをフローテーブルから取得する
  std::string action = select_string(std::to_string(pkt->get_tag()));
  if (!action) { // flowテーブルにエントリがなかった場合
    // 1. コントローラーに問い合わせる
    // 2. フローテーブルに値を入れる
    // 3. action = 問い合わせた結果
  }

  // actionを行う
}
