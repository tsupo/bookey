/*
 * UserInfo.cpp  : ソーシャルブックマーク管理プログラム
 *      CUserInfo クラス インプリメンテーション ファイル
 *          written by H.Tsujimura  6 Jun 2006
 *
 * $Log: /comm/bookey/UserInfo.cpp $
 * 
 * 4     09/06/22 22:31 tsupo
 * 0.63c版
 * 
 * 131   09/06/22 17:56 Tsujimura543
 * 日本語モード←→英語モード切替関連、修正
 * 
 * 3     09/06/18 0:53 tsupo
 * 0.63b版
 * 
 * 130   09/06/16 1:56 Tsujimura543
 * 「設定ファイルが壊れているようです。」を表示する条件を修正
 * 
 * 2     09/05/29 8:43 tsupo
 * 0.62版
 * 
 * 129   09/05/28 22:40 Tsujimura543
 * m_blogName を追加
 * 
 * 128   09/05/28 22:13 Tsujimura543
 * 同一アカウントで複数 tumbleblog を開設している場合の投稿先
 * tumbleblog を指定しての投稿を可能にした
 * 
 * 1     09/05/14 3:48 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 127   09/04/01 21:07 Tsujimura543
 * Twitter の OAuth に対応
 * 
 * 126   08/11/13 13:56 Tsujimura543
 * CUserInfo::CheckKeys() を修正 (ret の値の設定方法を修正)
 * 
 * 125   08/11/11 18:24 Tsujimura543
 * dumpBookmark() でコメントも出力するように変更 (デバッグ用)
 * 
 * 124   08/11/11 16:20 Tsujimura543
 * 「APIキーを使用して@niftyクリップから取得する」処理を追加
 * 
 * 123   08/11/11 15:10 Tsujimura543
 * 「APIキーを使用して@niftyクリップから削除する」処理を追加、動作確認した
 * 
 * 122   08/11/10 17:41 Tsujimura543
 * ApiKey も CheckKeys() のチェック対象にするようにした
 * 
 * 121   08/11/05 19:48 Tsujimura543
 * 「APIキーを使用して@niftyクリップへ登録する」処理を追加、動作確認した
 * 
 * 120   08/08/21 17:35 Tsujimura543
 * BlogPeople tags と BlogPeople IB のサポートを終了
 * 
 * 119   08/07/28 20:35 Tsujimura543
 * livedoorクリップに関して、従来の方法での「削除」に失敗した場合は、
 * del.icio.us互換APIによる「削除」を試みるようにしてみた(APIキー取得
 * 済みの場合のみ)
 * 
 * 118   08/07/26 0:33 Tsujimura543
 * Diigo の「削除」に対応
 * 
 * 117   08/07/25 22:16 Tsujimura543
 * Diigo 対応
 * 
 * 116   08/07/25 1:30 Tsujimura543
 * ブックマーク削除後、前方に未削除のブックマークが残っていないとき
 * でも、「1個前に戻る」ボタンが有効なままになってしまう不具合を修正
 * 
 * 115   08/05/21 14:09 Tsujimura543
 * 「同期」処理を修正(「一気に登録する」場合に &amp; を含む URL を
 * そのまま(&amp;のまま)登録してしまう不具合を修正)
 * 
 * 114   08/05/19 19:24 Tsujimura543
 * (1) 同期処理を見直し
 * (2) 「ローカルOPML」が絡む場合の同期処理を修正
 * 
 * 113   08/05/16 20:04 Tsujimura543
 * IDS_TTL_SYNCHRONIZE と IDS_TXT_SYNCHRONIZE を LoadString
 * するタイミングを修正
 * 
 * 112   08/05/15 23:25 Tsujimura543
 * InquiryBookmarkSub() を修正、ブックマーク取得失敗(0件)時に
 * エラーダイアログに http ステータスコードを表示するようにした
 * 
 * 111   08/05/14 15:04 Tsujimura543
 * はてなブックマークの場合のみ m_useMyTitle のデフォルト値を
 * false にする (仕様変更)
 * 
 * 110   08/01/22 15:08 Tsujimura543
 * InquiryBookmarkSub() を修正。全件取得に失敗した場合でも、1割以上
 * 取得することができた場合は、取得したブックマーク情報をそのまま保持
 * するようにした
 * 
 * 109   07/10/31 18:49 Tsujimura543
 * putTumblr() に引数(version)を追加
 * 
 * 108   07/10/31 17:16 Tsujimura543
 * tumblr への登録(投稿)に対応
 * 
 * 107   07/10/11 22:23 Tsujimura543
 * Yahoo! Japan の ID で newsing を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 106   07/10/10 1:50 Tsujimura543
 * BBAuth経由で Buzzurl を利用する場合の削除処理のユーザ名、パスワード
 * の取得・設定回りを修正
 * 
 * 105   07/10/05 2:42 Tsujimura543
 * BBAuth 対応関連の各種修正を実施
 * 
 * 104   07/09/14 23:16 Tsujimura543
 * Buzzurl へのアクセスに BBAuth を使っている場合の、ダイアログに
 * 表示するユーザ名、パスワードを Yahoo! Japan の ID とパスワード
 * にした
 * 
 * 103   07/09/13 22:30 Tsujimura543
 * Yahoo! Japan の ID で Buzzurl を利用できるようになったのに対応する
 * ための修正を実施
 * 
 * 102   07/09/10 15:01 Tsujimura543
 * DeleteBookmarks() を修正。削除用のブックマーク情報表示ダイアログの
 * URL に &amp; が含まれる場合は & に変換してから表示するようにした
 * 
 * 101   07/09/06 18:04 Tsujimura543
 * CUserInfoクラスのコピーコンストラクタ、代入演算子をCBookeyApp内で
 * 使っていたのを、CUserInfoクラス内に移管 (PutBookmarks)
 * 
 * 100   07/09/05 20:30 Tsujimura543
 * UserAgent 回りをリファクタリング
 * 
 * 99    07/07/09 20:00 Tsujimura543
 * digg への「登録」に対応
 * 
 * 98    07/05/23 16:11 Tsujimura543
 * Timelog への登録(発言)に対応
 * 
 * 97    07/05/11 19:10 Tsujimura543
 * Twitter に送る bookey の版数をリソースから取得したものを使うように
 * してみた
 * 
 * 96    07/04/20 23:15 Tsujimura543
 * Yahoo! Bookmarks と Yahoo! ブックマークの「削除」に対応
 * 
 * 95    07/04/20 20:34 Tsujimura543
 * Yahoo! ブックマーク、Yahoo! Bookmarks のインポートとエクスポートに対応
 * 
 * 94    07/04/18 21:37 Tsujimura543
 * Yahoo! Bookmarks (の「登録」のみ) に対応
 * 
 * 93    07/04/16 22:05 Tsujimura543
 * Yahoo! ブックマーク への「登録」に対応
 * 
 * 92    07/04/16 17:59 Tsujimura543
 * del.icio.us の posts/all 形式の XML ファイルのインポートとエクスポート
 * に対応した
 * 
 * 91    07/04/10 18:46 Tsujimura543
 * Twitter への「登録」に対応
 * 
 * 90    07/03/30 13:50 Tsujimura543
 * FC2BOOKMARK の「削除」にも対応
 * 
 * 89    07/03/29 23:04 Tsujimura543
 * FC2BOOKMARK に対応
 * 
 * 88    07/03/14 17:08 Tsujimura543
 * StdAfx.h をインクルードしなくてもいいようにした
 * 
 * 87    07/02/16 16:35 Tsujimura543
 * コメントを修正
 * 
 * 86    07/02/16 16:22 Tsujimura543
 * はてなブックマーク、Buzzurl、BlogPet気になる記事に関して、タイトルを上
 * 書きするかどうか選択(指定)できるようにした
 * 
 * 85    07/01/30 19:22 Tsujimura543
 * タグ一覧の取得、タグの削除、タグの置換を実際に行なう関数を UserInfo.cpp
 * から分離し、別のソースファイルに移管した
 * 
 * 84    07/01/30 0:00 Tsujimura543
 * 一部あいまいな記述を厳密化
 * 
 * 83    07/01/29 21:59 Tsujimura543
 * はてなブックマークの「タグの削除」、「タグの置換」にも対応した
 * 
 * 82    07/01/29 20:13 Tsujimura543
 * タグの一覧取得、タグの置換に関して、Blue Dot にも対応した
 * (Blue Dot はサーバ側からちゃんと応答が返ってこないことがよくあるが、
 * 応答が返ってきたときはちゃんと期待通りに動作することを確認した)
 * 
 * 81    07/01/29 17:51 Tsujimura543
 * タグ一覧の取得、タグの削除、タグの置換の各処理を追加
 * 
 * 80    07/01/19 15:38 Tsujimura543
 * MyClipEx 構造体のメンバ名を MyClip 構造体に合わせた
 * 
 * 79    07/01/18 0:53 Tsujimura543
 * デバッグ用のコード(の名残)を削除
 * 
 * 78    07/01/16 1:26 Tsujimura543
 * 英語モード対応
 * 
 * 77    07/01/13 1:42 Tsujimura543
 * CBookeyApp::CBookeyApp() の中から CString#LoadString() すると
 * assertion failed することが判明。対策を実施 (英語モード対応にあたって
 * 発生した障害)
 * 
 * 76    07/01/13 0:23 Tsujimura543
 * CFileDialog 関連部分をリファクタリング (兼・英語モード対応準備 その3)
 * 
 * 75    07/01/12 23:51 Tsujimura543
 * 英語モード対応準備 その2
 * 
 * 74    07/01/12 23:35 Tsujimura543
 * 英語モード対応準備
 * 
 * 73    07/01/11 17:01 Tsujimura543
 * 2007年1月10日付で「ECナビ人気ニュース」が Buzzurl に移行したのに
 * 伴う修正
 * 
 * 72    07/01/04 18:54 Tsujimura543
 * ShowWindow() の引数を修正
 * 
 * 71    06/12/25 23:23 Tsujimura543
 * 「BlogPet 気になる記事」に対応
 * 
 * 70    06/12/21 21:17 Tsujimura543
 * JoltMark の登録、取得に対応
 * 
 * 69    06/12/21 14:08 Tsujimura543
 * FC2BOOKMARK, 「BlogPet 気になる記事」対応準備
 * 
 * 68    06/12/06 19:48 Tsujimura543
 * コメントを修正
 * 
 * 67    06/12/06 19:46 Tsujimura543
 * livedoor Clip のエクスポートファイル(RSS 2.0 形式)をインポートする機能
 * を追加した
 * 
 * 66    06/12/04 19:19 Tsujimura543
 * NETSCAPE_BOOKMARK_FILE_1形式でのブックマーク情報出力時に
 * Shift_JIS での出力も選択できるようにした
 * 
 * 65    06/11/27 16:32 Tsujimura543
 * コメントを修正
 * 
 * 64    06/11/27 16:24 Tsujimura543
 * CUserInfo::PutBookmarks() 内で呼び出している CFileDialog のコンストラ
 * クタの第1引数を TRUE から FALSE に修正 (ファイルを上書きしていいか尋
 * ねるダイアログが出ない不具合への対処)
 * 
 * 63    06/11/16 16:43 Tsujimura543
 * CUserInfo 導入によるリファクタリング第16段階、終了
 * 
 * 62    06/11/16 14:02 Tsujimura543
 * CUserInfo 導入によるリファクタリング第15段階、終了
 * 
 * 61    06/11/10 19:26 Tsujimura543
 * ブラウザのブックマークを取り込む/ブラウザに取り込める形式のブックマーク
 * ファイルを生成する機能をサポートするための準備
 * 
 * 60    06/11/06 16:42 Tsujimura543
 * ResetUserInfo() に暫定的な対処を実施(「ローカルOPML」ファイル名の暫定的
 * な修復処理を追加)
 * 
 * 59    06/10/28 1:14 Tsujimura543
 * 「ローカルOPML」へ登録できないことがある不具合に対処
 * 
 * 58    06/10/26 23:52 Tsujimura543
 * 「1個前に戻る」で戻りすぎてしまうことがある(消したはずのブックマークが
 * 表示される)不具合に対処
 * 
 * 57    06/10/26 23:17 Tsujimura543
 * 「ローカル OPML」に対応
 * 
 * 56    06/10/07 1:09 Tsujimura543
 * Blue Dot に対応
 * 
 * 55    06/10/05 22:30 Tsujimura543
 * POOKMARK Airlines の「削除」に対応
 * 
 * 54    06/10/04 21:10 Tsujimura543
 * POOKMARK Airline → POOKMARK Airlines に修正
 * 
 * 53    06/10/04 21:03 Tsujimura543
 * POOKMARK Airline に対応
 * 
 * 52    06/09/29 19:38 Tsujimura543
 * newsing の m_bmSymbol の値を変更 (先頭の文字を小文字から大文字に変更)
 * 
 * 51    06/09/04 22:33 Tsujimura543
 * SleepEx() → Sleep() に置換
 * 
 * 50    06/09/04 22:28 Tsujimura543
 * DeleteBookmarks() を修正 (deleted の解放漏れ)
 * 
 * 49    06/09/04 18:16 Tsujimura543
 * 「削除」ダイアログと「同期」ダイアログに「1個前に戻る」機能を追加
 * 
 * 48    06/09/04 15:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 47c   06/09/03 22:13 tsupo
 * ブックマークの削除に失敗した場合、いきなり処理を中断するのはやめて、処
 * 理を続行するかどうか尋ねるようにした
 * 
 * 47b   06/09/03 19:26 tsupo
 * cookie 回りを修正 (メモリオーバーラン対策)
 * 
 * 47a   06/09/03 5:51 tsupo
 * Visual Studio 2500 でビルドした場合に出る warning (VC++ 6 では出ない
 * warning) に対処
 * 
 * 47    06/08/26 1:37 Tsujimura543
 * CUserInfo 導入によるリファクタリング第14段階、終了
 * 
 * 46    06/08/26 0:30 Tsujimura543
 * コメントを修正
 * 
 * 45    06/08/25 18:08 Tsujimura543
 * DeleteBookmarks() をリファクタリング
 * 
 * 44    06/08/23 21:37 Tsujimura543
 * 1470.netリニューアル版の同期の場合のユーザ情報設定処理も実装
 * (ただし、同期処理[のうち、取得側]本体は未実装) [→ 06/08/25 実装済み]
 * 
 * 43    06/08/23 21:35 Tsujimura543
 * 「1470.netリニューアル版のユーザ情報未設定のまま、削除を実行しようとし
 * たとき」のユーザ情報設定用ダイアログ表示処理回りを実装
 * 
 * 42    06/08/22 19:46 Tsujimura543
 * ドリコムRSSの削除処理、1470.netリニューアル版の削除処理の呼び出しを追加
 * 
 * 41    06/08/22 17:53 Tsujimura543
 * enum authenticationType → AUTH_TYPE
 * 
 * 40    06/08/22 15:46 Tsujimura543
 * struct myClip → MyClip に置換 (typedef struct myClip MyClip)
 * 
 * 39    06/08/22 11:41 Tsujimura543
 * #include する必要のないファイルをインクルードするのをやめた
 * 
 * 38    06/08/21 21:06 Tsujimura543
 * authType の値を「初期設定ファイル」に保存するようにした
 * 
 * 37    06/08/21 20:29 Tsujimura543
 * 「はてな認証API」経由での1470.netリニューアル版へのアクセスに対応
 * 
 * 36    06/08/18 15:05 Tsujimura543
 * ECナビ人気ニュースの「削除」に対応
 * 
 * 35    06/07/28 22:59 Tsujimura543
 * タブ切り替え式の「設定ダイアログ」を作成・導入した
 * 
 * 34    06/07/21 21:09 Tsujimura543
 * ニフティクリップの取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 33    06/07/21 20:51 Tsujimura543
 * ECナビ人気ニュースの取得処理の引数を追加(全何件あるか、取得できるように
 * した)
 * 
 * 32    06/07/21 20:17 Tsujimura543
 * BlogPeople Tags の取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 31    06/07/21 17:48 Tsujimura543
 * livedoorクリップの取得処理の引数を追加(全何件あるか、取得できるようにし
 * た)
 * 
 * 30    06/07/20 19:02 Tsujimura543
 * del.icio.us からの「取得」時、取得に失敗した場合、全何件中の何件までは
 * 取得に成功したか、ダイアログで表示するようにした
 * 
 * 29    06/07/19 14:19 Tsujimura543
 * MyClip! 関係の処理を削除 (2006年6月末でサービス終了のため)
 * 
 * 28    06/07/15 0:56 Tsujimura543
 * 1470.netリニューアル版への「登録」に対応
 * 
 * 27    06/07/14 18:17 Tsujimura543
 * (1) JoltMark, 1470.netリニューアル版 対応準備
 * (2) はてな認証API (1470.netリニューアル版向け) 対応準備
 * 
 * 26    06/07/12 17:34 Tsujimura543
 * ドリコムRSS(のClip!)の取得、同期に対応
 * 
 * 25    06/07/12 9:40 Tsujimura543
 * DeleteLivedoorClip() と DeleteNiftyClip() を追加
 * 
 * 24    06/07/07 19:34 Tsujimura543
 * ニフティクリップの取得、同期に対応
 * 
 * 23    06/07/06 19:53 Tsujimura543
 * livedoorクリップの取得、同期に対応
 * 
 * 22    06/07/05 18:19 Tsujimura543
 * CUserInfo 導入によるリファクタリング第13段階、終了
 * 
 * 21    06/07/05 17:49 Tsujimura543
 * CUserInfo 導入によるリファクタリング第12段階、終了
 * 
 * 20    06/07/04 10:34 Tsujimura543
 * 砂時計カーソル関連、修正
 * 
 * 19    06/07/03 15:15 Tsujimura543
 * ProceedingDialog 絡みの改修 (ProceedingDialog の delete時に例外が
 * 発生することがある件の対策実施)
 * 
 * 18    06/07/03 14:37 Tsujimura543
 * はてなブックマークの取得時に、全件取得できたかどうかチェックするように
 * した
 * 
 * 17    06/06/30 19:43 Tsujimura543
 * ECナビ人気ニュースの取得、同期に対応
 * 
 * 16    06/06/29 18:47 Tsujimura543
 * 「ECナビ人気ニュース」と「ニフティクリップ」の登録に各々対応した
 * 
 * 15    06/06/29 0:44 Tsujimura543
 * livedoorクリップ(の登録)に対応
 * 
 * 14    06/06/27 15:24 Tsujimura543
 * Flog の削除に対応
 * 
 * 13    06/06/23 21:50 Tsujimura543
 * Flog の取得、同期に対応した
 * 
 * 12    06/06/22 21:21 Tsujimura543
 * inquery → inquiry に修正(綴りミス)
 * 
 * 11    06/06/22 19:04 Tsujimura543
 * CBookeyView::SetBookeyInfo() を実行しても、設定が変更できなくなって
 * しまっていた(エンバグ)のを修正。変更できるようにした
 * 
 * 10    06/06/21 21:14 Tsujimura543
 * CUserInfo 導入によるリファクタリング第11段階、終了
 * 
 * 9     06/06/21 19:36 Tsujimura543
 * ブックマーク取得処理も別スレッド化した
 * 
 * 8     06/06/20 17:59 Tsujimura543
 * CUserInfo 導入によるリファクタリング第10段階、終了
 * 
 * 7     06/06/20 14:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第9段階、終了
 * 
 * 6     06/06/14 23:02 Tsujimura543
 * 「同期」処理中の進行状況表示ダイアログの文言を整理
 * 
 * 5a    06/06/15 16:41 Tsujimura543
 * CUserInfo 導入によるリファクタリング第8段階、終了
 * 
 * 5     06/06/14 22:40 Tsujimura543
 * CUserInfo 導入によるリファクタリング第7段階、終了
 * 
 * 4     06/06/14 11:44 Tsujimura543
 * CUserInfo 導入によるリファクタリング第5段階、終了
 * 
 * 3     06/06/07 20:25 Tsujimura543
 * CUserInfo 導入によるリファクタリング第4段階、終了
 * 
 * 2     06/06/07 15:33 Tsujimura543
 * CUserInfo 導入によるリファクタリング第3段階、終了
 * 
 * 1     06/06/06 22:24 Tsujimura543
 * 新規作成 (CUserInfo 導入によるリファクタリング第2段階、終了)
 * 
 * 0h    06/05/24 17:15 Tsujimura543
 * (1) URL に &amp; が含まれる場合は、いったん & に置換してから登録処理
 * を呼び出すようにした
 * (2) MM/Memo への「同期」時は、Amazon の商品ページに関しては、ASIN
 * が同じかどうか比較することで、登録済みかどうかを判断するようにした
 * 
 * 0g    06/05/11 16:01 Tsujimura543
 * コメントを整理
 * 
 * 0f    06/05/11 15:58 Tsujimura543
 * MM/Memo に関しては登録してから、実際に(取得結果に)反映されるまで時間が
 * かかることがあり、実際には登録済みにも関らず、未登録と判定され、同期(転
 * 送)が実行されてしまうことがある [メモ/今後の課題 → MM/Memo 側での対策
 * を待つしかないかもしれない]
 * 
 * 0e    06/05/11 15:56 Tsujimura543
 * 本来は同一のURLであるにも関らず、各サービス毎でURLを記憶・格納するとき
 * の形式(どの文字を数値参照、実態参照に変換するか/しないか)が異なるため、
 * 同一のURLであると判断できずに同期(転送)しようとしてしまうことがあった。
 * いったん、URLデコードしてから比較することで、同一のURLかどうか正しく判
 * 断できるようになった
 * 
 * 0d    06/02/17 22:02 Tsujimura543
 * 4つのブックマークサービスのうち、任意の2者間で同期が取れるようにした
 * 
 * 0c    06/02/17 18:07 Tsujimura543
 * ブックマークの同期を、はてなブックマークとdel.icio.us以外にも容易に対応
 * 可能にするため、処理の抽象化を進めた
 * 
 * 0b    05/11/10 22:25 Tsujimura543
 * 進行状況表示ダイアログを使うようにした
 * 
 * 0a    05/10/11 19:07 Tsujimura543
 * ブックマーク同期機能を実装 (動作確認済み)
 * 
 * 0     05/10/11 16:55 Tsujimura543
 * ブックマーク同期処理の実装開始
 */

#include "bookey.h"
#include "bookeyDlg.h"
#include "DeleteBookmarkDialog3.h"
#include "DeleteBookmarkDialog4.h"
#include "SynchronizeBookmarkDialog.h"
#include "importBookmark.h"
#include "exportBookmark.h"
#include "deleteBookmark.h"
#include "SettingDialog.h"
#include "parameter.h"
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "delicious.h"
#include "blueDot.h"
#include "hatenaAPI.h"
#ifdef __cplusplus
}
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/bookey/UserInfo.cpp 4     09/06/22 22:31 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void    SetUserAgent( char    *userAgent,
                      CString &str1,
                      CString &str2 )
{
    str1.LoadString( IDS_BOOKEY_VERSION );
    str2.LoadString( IDS_BOOKEY_WEB_URL );
    sprintf( userAgent, "bookey/%s (%s)", str1, str2 );
    setUserAgent( userAgent );
}

void    SetUserAgent( CString &str1,
                      CString &str2,
                      CString &str3 )
{
    char    userAgent[BUFSIZ];

    SetUserAgent( userAgent, str1, str2 );
    str3.LoadString( IDS_BOOKEY_RESOURCE_XML );
}

void    SetUserAgent( bool set )
{
    if ( set ) {
        char    userAgent[BUFSIZ];
        CString str1;
        CString str2;

        SetUserAgent( userAgent, str1, str2 );
    }
    else
        setUserAgent( NULL );
}


#ifdef  _DEBUG
void
dumpBookmark( int kind, const MyClip *mp, int num )
{
    const char  *name = "bookmark";
    char        filename[MAX_PATH];
    FILE        *fp;
    time_t      t = time( NULL );

    switch ( kind ) {
    case CUserInfo::BK_HATENA:
        name = "hatena";
        break;
    case CUserInfo::BK_DELICIOUS:
        name = "delicious";
        break;
    case CUserInfo::BK_MM_MEMO:
        name = "mmMemo";
        break;
    case CUserInfo::BK_DRECOM_RSS:
        name = "drecom";
        break;
    case CUserInfo::BK_FLOG:
        name = "flog";
        break;
    case CUserInfo::BK_LIVEDOOR_CLIP:
        name = "livedoor";
        break;
    case CUserInfo::BK_ECNAVI_CLIP:
        name = "buzzurl";
        break;
    case CUserInfo::BK_NIFTY_CLIP:
        name = "nifty";
        break;
    case CUserInfo::BK_1470NET:
        name = "1470net";
        break;
    case CUserInfo::BK_POOKMARK:
        name = "pookmark";
        break;
    case CUserInfo::BK_BLUEDOT:
        name = "blueDot";
        break;
    case CUserInfo::BK_JOLTMARK:
        name = "joltMark";
        break;
    case CUserInfo::BK_BLOGPET:
        name = "blogpet";
        break;
    case CUserInfo::BK_FC2BOOKMARK:
        name = "fc2";
        break;
    case CUserInfo::BK_YJ_BOOKMARK:
        name = "yahooJapan";
        break;
    case CUserInfo::BK_YAHOO_BOOKMARKS:
        name = "yahoo";
        break;
    case CUserInfo::BK_DIIGO:
        name = "diigo";
        break;
    case CUserInfo::BK_LOCAL_OPML:
        name = "localOpml";
        break;
    }

    sprintf( filename, "./%s_%d.txt", name, t );
    fp = fopen( filename, "w" );
    if ( !fp )
        return;

    fprintf( fp, "bookmark kind: %s\n\n", name );
    for ( int i = 0; i < num; i++ ) {
        fprintf( fp, "[%05d] url     = ===[%s]===\n", i + 1, mp[i].url );
        fprintf( fp,"        title   = ===[%s]===\n", mp[i].title );
        if ( mp[i].comment[0] != NUL )
            fprintf( fp,
                    "        comment = ===[%s]===\n", mp[i].comment );
    }

    fclose( fp );
}
#endif


/*
 *  初期化、ユーザ情報設定
 */

void    CUserInfo::Init()
{
    m_isTarget     = false;
    m_useMyTitle   = true;
    m_username     = "";
    m_password     = "";
    m_username2    = "";
    m_password2    = "";
    m_blogID       = "";
    m_blogName     = "";
    m_opmlFilename = "";
    m_apiKey       = "";
    m_secret       = "";
    m_authType     = AK_ORIGINAL;

    m_tgt_hatenaBookmark = "";
    m_tgt_delicious      = "";
    m_tgt_mmMemo         = "";
    m_tgt_drecomRSS      = "";
    m_tgt_flog           = "";
    m_tgt_livedoorClip   = "";
    m_tgt_ecNaviClip     = "";
    m_tgt_niftyClip      = "";
    m_tgt_1470net        = "";
    m_tgt_pookmark       = "";
    m_tgt_blueDot        = "";
    m_tgt_joltMark       = "";
    m_tgt_blogPet        = "";
    m_tgt_fc2bookmark    = "";
    m_tgt_yjBookmark     = "";
    m_tgt_yahooBookmarks = "";
    m_tgt_diigo          = "";
    m_tgt_hatenaFeed     = "";
    m_tgt_deliciousXML   = "";
}

void    CUserInfo::Init( bool isTarget, CString username, CString password )
{
    m_isTarget = isTarget;
    m_username = username;
    m_password = password;
    m_authType = AK_ORIGINAL;
}

void    CUserInfo::Init( enum bookmarkType bmType )
{
    Init();
    m_bmType = bmType;

    switch ( m_bmType ) {
    case BK_HATENA:
        m_bmName.LoadString( IDS_TGT_HATENA_BOOKMARK );
        m_bmSymbol   = "Hatena";
        m_useMyTitle = false; // はてブの場合のみ false をデフォルトにする
        break;
    case BK_DELICIOUS:
        m_bmName.LoadString( IDS_TGT_DELICIOUS );
        m_bmSymbol = "Delicious";
        break;
    case BK_MM_MEMO:
        m_bmName.LoadString( IDS_TGT_MMMEMO );
        m_bmSymbol = "MMmemo";
        m_authType = AK_TYPEKEY;
        break;
    case BK_DRECOM_RSS:
        m_bmName.LoadString( IDS_TGT_DRECOM_RSS );
        m_bmSymbol = "DrecomRSS";
        break;
    case BK_FLOG:
        m_bmName.LoadString( IDS_TGT_FLOG );
        m_bmSymbol = "Flog";
        break;
    case BK_LIVEDOOR_CLIP:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_CLIP );
        m_bmSymbol = "Livedoor";
        break;
    case BK_ECNAVI_CLIP:
        m_bmName.LoadString( IDS_TGT_ECNAVI_CLIP );
        m_bmSymbol = "EcNavi";
        break;
    case BK_NIFTY_CLIP:
        m_bmName.LoadString( IDS_TGT_NIFTY_CLIP );
        m_bmSymbol = "Nifty";
        break;
    case BK_JOLTMARK:
        m_bmName.LoadString( IDS_TGT_JOLTMARK );
        m_bmSymbol = "JoltMark";
        break;
    case BK_1470NET:
        m_bmName.LoadString( IDS_TGT_1470NET );
        m_bmSymbol = "1470.net";
        m_authType = AK_TYPEKEY; /* default は TypeKey 認証とする */
        break;
    case BK_NEWSING:
        m_bmName.LoadString( IDS_TGT_NEWSING );
        m_bmSymbol = "Newsing";
        break;
    case BK_POOKMARK:
        m_bmName.LoadString( IDS_TGT_POOKMARK );
        m_bmSymbol = "Pookmark";
        m_authType = AK_JUGEMKEY;   /* POOKMARK は jugemkey 認証 */
        break;
    case BK_BLUEDOT:
        m_bmName.LoadString( IDS_TGT_BLUEDOT );
        m_bmSymbol = "BlueDot";
        break;
    case BK_FC2BOOKMARK:
        m_bmName.LoadString( IDS_TGT_FC2_BOOKMARK );
        m_bmSymbol = "FC2BOOKMARK";
        break;
    case BK_BLOGPET:
        m_bmName.LoadString( IDS_TGT_BLOGPET );
        m_bmSymbol = "BlogPet";
        break;
    case BK_TWITTER:
        m_bmName.LoadString( IDS_TGT_TWITTER );
        m_bmSymbol = "Twitter";
        break;
    case BK_YJ_BOOKMARK:
        m_bmName.LoadString( IDS_TGT_YJ_BOOKMARK );
        m_bmSymbol = "YahooJapanBookmark";
        break;
    case BK_YAHOO_BOOKMARKS:
        m_bmName.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
        m_bmSymbol = "YahooBookmarks";
        break;
    case BK_TIMELOG:
        m_bmName.LoadString( IDS_TGT_TIMELOG );
        m_bmSymbol = "Timelog";
        break;
    case BK_DIGG:
        m_bmName.LoadString( IDS_TGT_DIGG );
        m_bmSymbol = "Digg";
        break;
    case BK_TUMBLR:
        m_bmName.LoadString( IDS_TGT_TUMBLR );
        m_bmSymbol = "tumblr";
        break;
    case BK_DIIGO:
        m_bmName.LoadString( IDS_TGT_DIIGO );
        m_bmSymbol = "Diigo";
        break;
    case BK_LOCAL_OPML:
        m_bmName.LoadString( IDS_TGT_LOCAL_OPML );
        m_bmSymbol     = "LocalOpml";
        m_opmlFilename = BOOKEY_DEFAULT_OPML;
        break;
    case BK_NETSCAPE_BOOKMARK_FILE_1:
        m_bmName.LoadString( IDS_TGT_NETSCAPE_1 );
        break;
    case BK_OPERA6_ADR:
        m_bmName.LoadString( IDS_TGT_OPERA_6 );
        break;
    case BK_HATENA_BOOKMARK_ATOM:
        m_bmName.LoadString( IDS_TGT_HATENA_FEED );
        break;
    case BK_LIVEDOOR_CLIP_RSS:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_FEED );
        break;
    case BK_DELICIOUS_XML:
        m_bmName.LoadString( IDS_TGT_DELICIOUS_XML );
        break;
    }
}

void    CUserInfo::ReInit()
{
    switch ( m_bmType ) {
    case BK_HATENA:
        m_bmName.LoadString( IDS_TGT_HATENA_BOOKMARK );
        break;
    case BK_DELICIOUS:
        m_bmName.LoadString( IDS_TGT_DELICIOUS );
        break;
    case BK_MM_MEMO:
        m_bmName.LoadString( IDS_TGT_MMMEMO );
        break;
    case BK_DRECOM_RSS:
        m_bmName.LoadString( IDS_TGT_DRECOM_RSS );
        break;
    case BK_FLOG:
        m_bmName.LoadString( IDS_TGT_FLOG );
        break;
    case BK_LIVEDOOR_CLIP:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_CLIP );
        break;
    case BK_ECNAVI_CLIP:
        m_bmName.LoadString( IDS_TGT_ECNAVI_CLIP );
        break;
    case BK_NIFTY_CLIP:
        m_bmName.LoadString( IDS_TGT_NIFTY_CLIP );
        break;
    case BK_JOLTMARK:
        m_bmName.LoadString( IDS_TGT_JOLTMARK );
        break;
    case BK_1470NET:
        m_bmName.LoadString( IDS_TGT_1470NET );
        break;
    case BK_NEWSING:
        m_bmName.LoadString( IDS_TGT_NEWSING );
        break;
    case BK_POOKMARK:
        m_bmName.LoadString( IDS_TGT_POOKMARK );
        break;
    case BK_BLUEDOT:
        m_bmName.LoadString( IDS_TGT_BLUEDOT );
        break;
    case BK_FC2BOOKMARK:
        m_bmName.LoadString( IDS_TGT_FC2_BOOKMARK );
        break;
    case BK_BLOGPET:
        m_bmName.LoadString( IDS_TGT_BLOGPET );
        break;
    case BK_TWITTER:
        m_bmName.LoadString( IDS_TGT_TWITTER );
        break;
    case BK_YJ_BOOKMARK:
        m_bmName.LoadString( IDS_TGT_YJ_BOOKMARK );
        break;
    case BK_YAHOO_BOOKMARKS:
        m_bmName.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
        break;
    case BK_TIMELOG:
        m_bmName.LoadString( IDS_TGT_TIMELOG );
        break;
    case BK_DIGG:
        m_bmName.LoadString( IDS_TGT_DIGG );
        break;
    case BK_TUMBLR:
        m_bmName.LoadString( IDS_TGT_TUMBLR );
        break;
    case BK_DIIGO:
        m_bmName.LoadString( IDS_TGT_DIIGO );
        break;
    case BK_LOCAL_OPML:
        m_bmName.LoadString( IDS_TGT_LOCAL_OPML );
        break;
    case BK_NETSCAPE_BOOKMARK_FILE_1:
        m_bmName.LoadString( IDS_TGT_NETSCAPE_1 );
        break;
    case BK_OPERA6_ADR:
        m_bmName.LoadString( IDS_TGT_OPERA_6 );
        break;
    case BK_HATENA_BOOKMARK_ATOM:
        m_bmName.LoadString( IDS_TGT_HATENA_FEED );
        break;
    case BK_LIVEDOOR_CLIP_RSS:
        m_bmName.LoadString( IDS_TGT_LIVEDOOR_FEED );
        break;
    case BK_DELICIOUS_XML:
        m_bmName.LoadString( IDS_TGT_DELICIOUS_XML );
        break;
    }
}

/*
 *  ユーザ情報取得
 */

void    CUserInfo::GetUserInfo( CString &username,
                                CString &password,
                                enum bookmarkType &bmType )
{
    if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        username = pp->m_yjBookmark.m_username;
        password = pp->m_yjBookmark.m_password;
    }
    else {
        if ( m_username.GetLength() > 0 )
            username = m_username;
        if ( m_password.GetLength() > 0 )
            password = m_password;
    }
    bmType = m_bmType;
}


/*
 *  ユーザ情報表示
 */

void    CUserInfo::SetWindowText( CString &username,
                                  CString &password,
                                  CEdit   *editUsername,
                                  CEdit   *editPassword )
{
    username = _T("");
    password = _T("");
    if ( ((m_bmType == BK_ECNAVI_CLIP) ||
          (m_bmType == BK_NEWSING)        )   &&
         (m_authType == AK_YAHOOJAPAN_BBAUTH)    ) {
        if ( (m_username2.GetLength() > 0) &&
             (m_password2.GetLength() > 0)    ) {
            username = (const char *)m_username2;
            password = (const char *)m_password2;
        }
        else {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            username = pp->m_yjBookmark.m_username;
            password = pp->m_yjBookmark.m_password;
        }
    }
    else {
        if ( m_username.GetLength() > 0 )
            username = (const char *)m_username;
        if ( m_password.GetLength() > 0 )
            password = (const char *)m_password;
    }

    editUsername->SetWindowText( username );
    editPassword->SetWindowText( password );
}

void    CUserInfo::SetWindowText( CString &username,
                                  CEdit   *editUsername )
{
    if ( m_username.GetLength() > 0 ) {
        username = (const char *)m_username;
        editUsername->SetWindowText( username );
    }
}


/*
 *  ユーザ名、パスワードの設定
 */

void    CUserInfo::SetBookeyInfo()
{
    int ret = IDNO;

    ret = InquiryToUseService();
    if ( ret == IDYES ) {
        DeleteBookmarkDialog3   dlg3;
        dlg3.m_messageOnCancel = "**";

        GetUserInfo( dlg3.m_username, dlg3.m_password,
                     dlg3.m_targetBookmark );
        ret = dlg3.DoModal();
        if ( ret == IDOK )
            Init( true, dlg3.m_username, dlg3.m_password );
    }
    else
        Init( false );
}


/*
 *  各種問い合わせ
 */

int     CUserInfo::InquiryToUseService()
{
    int     ret = IDNO;
    char    txt[BUFSIZ];
    CString title;
    CString text;

    title.LoadString(IDS_TTL_SYNC_TARGET);
    text.LoadString( IDS_TXT_SYNC_TARGET);

    m_isTarget = false;

#if 0
    strcpy( txt, (const char *)m_bmName );
    strcat( txt, " をブックマーク同時登録対象にしますか?    " );
#else
    sprintf( txt, text, (const char *)m_bmName );
#endif
    ret = ::MessageBox(
                NULL,
                txt,
                title,  // ブックマーク同時登録対象設定
                MB_YESNO|MB_ICONQUESTION );

    return ( ret );
}

bool    CUserInfo::InquiryUserInfo( CString bookmark1, CString bookmark2, 
                                    CString txt )
{
    if ( m_bmType == BK_LOCAL_OPML )
        return ( true );

    DeleteBookmarkDialog3   dlg3;

    if ( (bookmark1.Compare( m_bmName ) == 0) ||
         (bookmark2.Compare( m_bmName ) == 0)    ) {
    	DeleteBookmarkDialog3   dlg3;

        dlg3.m_messageOnCancel = txt;

        GetUserInfo( dlg3.m_username, dlg3.m_password,
                     dlg3.m_targetBookmark );

        if ( m_bmType != BK_1470NET ) {
            int ret = dlg3.DoModal();
            if ( (ret == IDCANCEL)                  ||
                 (dlg3.m_username.GetLength() == 0) ||
                 (dlg3.m_password.GetLength() == 0)    )
                return ( false );

            if ( (dlg3.m_username.GetLength() > 0)           &&
                 ((m_username.GetLength() == 0)         ||
                  dlg3.m_username.Compare( m_username )    )    )
                m_username = dlg3.m_username;

            if ( (dlg3.m_password.GetLength() > 0)           &&
                 ((m_password.GetLength() == 0)         ||
                  dlg3.m_password.Compare( m_password )    )    )
                m_password = dlg3.m_password;
        }
        else {
            if ( dlg3.m_username.GetLength() == 0 ) {
                if ( m_username.GetLength() == 0 ) {
                    SettingDialog   sdlg;
                    sdlg.m_1470net = true;
                    sdlg.DoModal();

                    m_authType = sdlg.m_dlg08.m_authType;
                    m_username = sdlg.m_dlg08.m_username;
                    m_password = sdlg.m_dlg08.m_password;
                }
                dlg3.m_username = m_username;
                dlg3.m_password = m_password;
                if ( (dlg3.m_username.GetLength() == 0) ||
                     (dlg3.m_password.GetLength() == 0)    )
                    return ( false );
            }
        }
    }

    return ( true );
}


/*
 *  ユーザ情報再設定
 */

void    CUserInfo::ResetUserInfo( bool &needToSave )
{
    if ( m_bmType == BK_LOCAL_OPML ) {
        if ( m_isTarget ) {
            if ( m_opmlFilename.GetLength() == 0 )
                m_opmlFilename = BOOKEY_DEFAULT_OPML;
            if ( !m_opmlFilename.Compare( BOOKEY_DEFAULT_OPML ) )
                needToSave = true;
        }
        return;
    }

    if ( m_isTarget &&
         (m_username.GetLength() >  0) &&
         (m_password.GetLength() == 0) &&
         (m_secret.GetLength()   == 0)    ) {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_BROKEN_SETTING);
        text.LoadString( IDS_TXT_BROKEN_SETTING);

#if 0
        CString txt;

        txt = "設定ファイルが壊れているようです。\r\n「";
        txt += m_bmName;
        txt += "」の login 用パスワードを再設定してください。  ";
#else
        char    txt[BUFSIZ];

        sprintf( txt, text, (const char *)m_bmName );
#endif

        MessageBox( NULL,
                    txt,
                    title,  // 設定ファイル異常
                    MB_OK|MB_ICONWARNING );

        /* パスワード再設定 */
        DeleteBookmarkDialog3   dlg;
        dlg.m_messageOnCancel = "**";
        GetUserInfo( dlg.m_username, dlg.m_password,
                     dlg.m_targetBookmark );
        dlg.m_password = "";

        int ret = dlg.DoModal();
        if ( ret == IDOK ) {
            Init( true, dlg.m_username, dlg.m_password );
            needToSave = true;
        }
    }
}

void    CUserInfo::ResetUserInfo( bool &needToSave,
                                  BOOL &isTarget,
                                  char *username, char *password )
{
    if ( m_isTarget &&
         (m_username.GetLength() > 0) ) {
        if ( m_password.GetLength() == 0 ) {
            /* パスワード未設定、もしくはパスワードが壊れている場合 */
            DeleteBookmarkDialog3   dlg;
            CString                 action;

            action.LoadString( IDS_REGISTER );
            dlg.m_messageOnCancel = action; // 登録
            GetUserInfo( dlg.m_username, dlg.m_password,
                         dlg.m_targetBookmark );
            dlg.m_password = "";

            int ret = dlg.DoModal();
            if ( ret == IDOK ) {
                Init( true, dlg.m_username, dlg.m_password );
                needToSave = true;
            }
            else
                return;
        }

        strcpy( username, (const char *)m_username );
        strcpy( password, (const char *)m_password );
    }
    else
        username[0] = NUL;
    isTarget = m_isTarget;
}

void    CUserInfo::ResetUserInfo( bool &needToSave,
                                  BOOL &isTarget,
                                  char *filename )
{
    if ( m_isTarget && (m_opmlFilename.GetLength() == 0) ) {
        ResetUserInfo( needToSave );
        if ( m_opmlFilename.GetLength() == 0 ) {
            // ローカルOPMLファイル名が未設定の場合
            CString title;
            CString text;

            title.LoadString(IDS_TTL_NO_SETTING_LOCAL_OPML);
            text.LoadString( IDS_TXT_NO_SETTING_LOCAL_OPML);

            MessageBox( NULL,
                        text,   // ローカルOPMLファイル名が設定されていません。\r\n
                                // ローカルOPMLファイル名を設定しておいてください。
                        title,  // ローカルOPMLファイル名未設定
                        MB_OK|MB_ICONWARNING );

            filename[0] = NUL;
            isTarget    = false;
            return;
        }
    }

    if ( m_opmlFilename.GetLength() > 0 )
        strcpy( filename, m_opmlFilename );
    else
        filename[0] = NUL;
    isTarget = m_isTarget;
}


/*
 *  ブックマークのインポート(登録)
 */

void    CUserInfo::ImportFromAnotherToOne(
                const MyClip     *myAnother,
                int              numOfAnother,
                const MyClip     *myOne,
                int              numOfOne,
                const char       *anotherBookmarkName,
                ProceedingDialog *dlg
            )
{
    // myAnother のみに登録されていて myOne には登録されてい
    // ないブックマークを myOne に登録する
    bool    found     = false;
    bool    withQuery = true;
    int     cnt       = 0;
    int     first     = 0;
    CString title;
    CString dir;
    CString text;
    char    txt[BUFSIZ];
    BOOL    *synchronized = new BOOL[numOfAnother]; /* 同期済みフラグ */

    CWaitCursor cur;    // マウスカーソルを砂時計表示

    text.LoadString( IDS_DIRECTION );
    dir  = anotherBookmarkName;
    dir += text;    // →
    dir += m_bmName;

    CString tgt_localOPML;
    tgt_localOPML.LoadString( IDS_TGT_LOCAL_OPML );

    for ( int i = 0; i < numOfAnother; i++ ) {
        title.LoadString(IDS_TTL_SYNCHRONIZE);
        text.LoadString( IDS_TXT_SYNCHRONIZE);
        synchronized[i] = FALSE;
            /* 同期済みフラグ                                 */
            /*   TRUE:  同期済み or 同期する必要なし          */
            /*   FALSE: 同期する必要あり and まだ同期してない */
        dlg->ShowWindow( SW_SHOWNORMAL );
        dlg->ChangeDialogText( title,   // ブックマークの同期
                               text );  // 同期する必要のあるブックマークを探索中 ……
        found = false;
        for ( int j = 0; j < numOfOne; j++ ) {
            if ( !strcmp( myAnother[i].url, myOne[j].url )       ||
                 (strchr( myAnother[i].url, '%' )            &&
                  !strcmpi( myAnother[i].url, myOne[j].url )   )    ) {
                found = true;
                break;
            }
        
            if ( (strstr( myAnother[i].url, "&amp;" ) && 
                  strchr( myOne[j].url, '&' )            ) ||
                 (strstr( myOne[j].url, "&amp;" ) && 
                  strchr( myAnother[i].url, '&' )    )     ||
                 (strchr( myAnother[i].url, '%' ) &&
                  strchr( myOne[j].url,  '%' )       )        ) {
                char        url1[2048];
                char        url2[2048];
                const char  *p;

                strcpy( url1, myAnother[i].url );
                while ( ( p = strstr( url1, "&amp;" ) ) != NULL )
                    strcpy( (char *)p + 1, p + 5 );
                strcpy( url1, decodeURL( url1 ) );

                strcpy( url2, myOne[j].url );
                while ( ( p = strstr( url2, "&amp;" ) ) != NULL )
                    strcpy( (char *)p + 1, p + 5 );
                strcpy( url2, decodeURL( url2 ) );

                if ( !strcmpi( url1, url2 ) ) {
                    found = true;
                    break;
                }
            }

            if ( m_bmType == BK_MM_MEMO ) {
                // MM/Memo では Amazon の商品の URL だけ特別な扱いが必要
                if ( !strncmp( myAnother[i].url,
                               "http://www.amazon.co.jp/", 24 ) &&
                     !strncmp( myOne[j].url,
                               "http://www.amazon.co.jp/", 24 )    ) {
                    char    asin1[16];
                    char    asin2[16];

                    if (strstr( myAnother[i].url, "/gp/product/images/") &&
                        !strstr(myOne[j].url,     "/gp/product/images/")   ) {
                        synchronized[i] = TRUE; /* 同期する必要なし */
                        continue;
                    }

                    asin1[0] = NUL;
                    asin2[0] = NUL;
                    getASIN( myAnother[i].url, asin1 );
                    getASIN( myOne[j].url,     asin2 );
                    if ( asin1[0] && asin2[0]   &&
                         (asin1[0] == asin2[0]) &&
                         !strcmp( &(asin1[1]), &(asin2[1]) ) ) {
                        /* ASIN が一致したら、同一ページであるとみなす */
                        found = true;
                        break;
                    }
                }
            }
        }
        if ( found ) {
            synchronized[i] = TRUE; /* 同期する必要なし */
            continue;
        }

        dlg->ShowWindow( SW_HIDE );
        cnt++;
        if ( cnt == 1 ) {
            text.LoadString(IDS_TXT_START_SYNCHRONIZING);
            sprintf( txt, text, (const char *)dir );
            MessageBox( NULL,
                        txt,    // %s 方向のブックマークの同期を行ないます
                        title,  // ブックマークの同期
                        MB_OK|MB_ICONINFORMATION );
            first = i;
        }

        const char  *p;
        while ( (p = strstr( myAnother[i].url, "&amp;" )) != NULL )
            strcpy( (char *)p + 1, p + 5 ); /* "&amp;" を "&" へ置換*/

        if ( withQuery ) {
            // ブックマーク情報を表示
            DeleteBookmarkDialog4   dlg4;

            dlg4.m_url     = myAnother[i].url;
            dlg4.m_title   = myAnother[i].title;
            dlg4.m_comment = myAnother[i].comment;
            dlg4.m_tags    = myAnother[i].tags;

            if ( !strcmp( anotherBookmarkName, tgt_localOPML ) ) {
                char    *pp;

                pp = utf2sjis( myAnother[i].title );
                dlg4.m_title   = pp ? pp : myAnother[i].title;

                pp = utf2sjis( myAnother[i].comment );
                dlg4.m_comment = pp ? pp : myAnother[i].comment;

                pp = utf2sjis( myAnother[i].tags );
                dlg4.m_tags    = pp ? pp : myAnother[i].tags;
            }

            dlg4.m_messageOnQuery.LoadString(IDS_REGISTER4); // 登録
            dlg4.m_windowTextExtra  = "(" + dir + ")";
            dlg4.m_enableToBackward = (i == first) ? false : true;
            dlg4.m_backToPrevious   = false;

            int r = dlg4.DoModal();
            if ( r == IDCANCEL ) {
                withQuery = false;
                break;
            }
            if ( dlg4.m_backToPrevious ) {
                int j = i;
                while ( (--i > 0) && synchronized[i] )
                    ;
                if ( synchronized[i] == FALSE ) {
                    i--;
                    continue;
                }
                i = j;
            }
            if ( dlg4.m_executeWithoutQuery == true ) {
                CString title;
                CString text;

                title.LoadString(IDS_TTL_PUT_ALL_BOOKMARKS);
                text.LoadString( IDS_TXT_PUT_ALL_BOOKMARKS);
                sprintf( txt, text, (const char *)dir );
                r = MessageBox( NULL,
                                text,   // 残りのブックマークを全部一気に登録してしまっても構わないですね?
                                txt,    // (%s) ブックマーク一括登録確認
                                MB_YESNO|MB_ICONQUESTION );
                if ( r == IDYES )
                    withQuery = false;
            }
            if ( dlg4.m_execute == false )
                continue;
        }

        text.LoadString(IDS_TXT_CONTINUE_SYNCHRONIZING);
        sprintf( txt, text, (const char *)dir );
        dlg->ShowWindow( SW_SHOWNORMAL );
        dlg->ChangeDialogText( title,   // ブックマークの同期
                               txt );   // %s 転送中 ……
        PutBookmarks( &(myAnother[i]), dlg, true );
        synchronized[i] = TRUE; /* 同期済み */
    }

    if ( cnt == 0 ) {
        text.LoadString(IDS_TXT_NO_SYNCHRONIZING);
        sprintf( txt, text, (const char *)dir );
        MessageBox( NULL,
                    txt,    // %s 方向へ転送する必要のあるブックマークは見つかりませんでした
                    title,  // ブックマークの同期
                    MB_OK|MB_ICONINFORMATION );
    }
    else if ( withQuery ) {
        text.LoadString(IDS_TXT_END_SYNCHONIZING);
        sprintf( txt, text, (const char *)dir );
        MessageBox( NULL,
                    txt,    // %s 方向への同期が終わりました
                    title,  // ブックマークの同期
                    MB_OK|MB_ICONINFORMATION );
    }

    delete [] synchronized;
}

void    CUserInfo::ImportFromAnotherToOne(
                CString bookmark1,      CString bookmark2, 
                MyClip  *myBookmark1,   MyClip  *myBookmark2,
                int     numOfBookmark1, int     numOfBookmark2,
                int     direction )
{
    if ( (bookmark1.Compare( m_bmName ) == 0) ||
         (bookmark2.Compare( m_bmName ) == 0)    ) {
        ProceedingDialog    dlg;
        CWaitCursor         cur;    // マウスカーソルを砂時計表示

        dlg.Create( IDD_PROCEEDING_DIALOG );

        if ( ((direction == SynchronizeBookmarkDialog::fromBM1toBM2) &&
              (bookmark2.Compare( m_bmName ) == 0)          ) ||
             ((direction == SynchronizeBookmarkDialog::fromBM2toBM1) &&
              (bookmark1.Compare( m_bmName ) == 0)          ) ||
             ((direction == SynchronizeBookmarkDialog::both)         &&
              ((bookmark1.Compare( m_bmName ) == 0) ||
               (bookmark2.Compare( m_bmName ) == 0)    )    )    ) {
            // OneBookmark の中身を AnotherBookmark に登録
            MyClip      *myOne;
            int         numOfOneBookmarks;
            MyClip      *myAnother;
            int         numOfAnother;
            const char  *anotherBookmarkName;

            if ( bookmark1.Compare( m_bmName ) == 0 ) {
                myOne               = myBookmark1;
                numOfOneBookmarks   = numOfBookmark1;
                myAnother           = myBookmark2;
                numOfAnother        = numOfBookmark2;
                anotherBookmarkName = (const char*)bookmark2;
            }
            else {
                myOne               = myBookmark2;
                numOfOneBookmarks   = numOfBookmark2;
                myAnother           = myBookmark1;
                numOfAnother        = numOfBookmark1;
                anotherBookmarkName = (const char*)bookmark1;
            }

            ImportFromAnotherToOne( myAnother, numOfAnother,
                                    myOne,     numOfOneBookmarks,
                                    anotherBookmarkName,
                                    &dlg );
        }
    }
}


/*
 *  ブックマークのエクスポート(取得)
 */

bool    CUserInfo::ExportFromAnother(
                CString bookmark1,       CString bookmark2, 
                MyClip  **myBookmark1,   MyClip  **myBookmark2,
                int     *numOfBookmark1, int     *numOfBookmark2 )
{
    bool    cont = true;

    if ( (bookmark1.Compare( m_bmName ) == 0) ||
         (bookmark2.Compare( m_bmName ) == 0)    ) {
        MyClip  **myAnother;
        int     *numOfAnother;

        if ( bookmark1.Compare( m_bmName ) == 0 ) {
            myAnother    = myBookmark1;
            numOfAnother = numOfBookmark1;
        }
        else {
            myAnother    = myBookmark2;
            numOfAnother = numOfBookmark2;
        }

        cont = ExportFromAnother( myAnother, numOfAnother );

        switch ( m_bmType ) {
        case BK_MM_MEMO:
            if ( *numOfAnother > 0 ) {
                for ( int i = 0; i < *numOfAnother; i++ ) {
                    strcpy( (*myAnother)[i].title,
                            euc2sjis((*myAnother)[i].title) );
                    strcpy( (*myAnother)[i].comment,
                            euc2sjis((*myAnother)[i].comment) );
                    strcpy( (*myAnother)[i].tags,
                            euc2sjis((*myAnother)[i].tags) );
                }
            }
            break;
        }
    }

    return ( cont );
}

bool    CUserInfo::ExportFromAnother(
            MyClip **myAnother,
            int    *numOfAnother )
{
    bool        retry = false;
    CWaitCursor cur;    // マウスカーソルを砂時計表示

    // ブックマーク全取得
    do {
        retry = false;
        *myAnother = GetBookmarks( numOfAnother );
        if ( !(*myAnother) ) {
            int     r;
            char    txt[BUFSIZ];
            CString title;
            CString text;

            title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS_NOT_EXIST);
            text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS_NOT_EXIST);

            sprintf( txt, text, (const char *)m_bmName );
            r = MessageBox( NULL,
                            txt,
                            title,  // ブックマーク取得失敗(またはブックマークが存在しない)
                            MB_YESNOCANCEL|MB_ICONWARNING );
            if ( r == IDYES )
                retry = true;
            else if ( r == IDNO )
                break;
            else
                return ( false );
        }
    } while ( retry == true );

    return ( true );
}


/*
 *  ブックマークの削除
 */

void    CUserInfo::DeleteBookmarks(
            const char       *username,
            const char       *password,
            const char       *username2,
            const char       *password2,
            AUTH_TYPE        authType,
            bool             withQuery /* = true */,
            ProceedingDialog *dlg      /* = NULL */
        )
{
    CString title;
    CString text;

    if ( withQuery == false ) {
        title.LoadString(IDS_TTL_DELETE_ALL_BOOKMARKS);
        text.LoadString( IDS_TXT_DELETE_ALL_BOOKMARKS);
        int r = MessageBox( NULL,
                            text,   // 本当にブックマークを全部削除してしまっても構わないんですね?
                            title,  // ブックマーク削除確認
                            MB_YESNO|MB_ICONQUESTION );
        if ( r == IDNO )
            return;
    }

    CWaitCursor         cur;    // マウスカーソルを砂時計表示
    BOOL                ret;
    char                cookie[MAX_COOKIE_LEN];
    MyClipEx            *mp;
    int                 numOfClips = 0;
    ProceedingDialog    *pdlg;

    cookie[0] = NUL;

    if ( dlg )
        pdlg = dlg;
    else {
        pdlg = new ProceedingDialog();
        pdlg->Create( IDD_PROCEEDING_DIALOG );
    }

    /* 削除用エントリID一覧の 取得 */
    DBSparam_t param;

    param.myBookmark     = NULL;
    param.numOfBookmarks = 0;
    param.bookmarkKind   = m_bmType;
    memset( param.cookie, 0x00, MAX_COOKIE_LEN + 1 );
    param.cookieSize     = MAX_COOKIE_LEN;
    param.dlg            = pdlg;
    param.u.authType     = authType;
    strcpy( param.u.username, username );
    strcpy( param.u.password, password );
    if ( username2 )
        strcpy( param.u.username2, username2 );
    else
        param.u.username2[0] = NUL;
    if ( password2 )
        strcpy( param.u.password2, password2 );
    else
        param.u.password2[0] = NUL;

    mp = GetBookmarksForDelete( &param, numOfClips );
    if ( !mp || (numOfClips == 0) ) {
        if ( mp )
            free( mp );

        title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARKS);
        text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARKS);
        MessageBox( NULL,
                    text,   // ブックマーク情報を取得できませんでした
                    title,  // ブックマーク取得失敗
                    MB_OK|MB_ICONWARNING );
        if ( !dlg )
            delete pdlg;
        return;
    }

    // ブックマークを1件づつ削除
    strcpy( cookie, param.cookie );
    BOOL    *deleted = new BOOL[numOfClips];
    int     i;
    for ( i = 0; i < numOfClips; i++ )
        deleted[i] = FALSE;
    for ( i = 0; i < numOfClips; i++ ) {
        if ( deleted[i] == TRUE )
            continue;
        if ( withQuery ) {
            pdlg->ShowWindow( SW_HIDE );

            // ブックマーク情報を表示
            DeleteBookmarkDialog4   d;
            const char              *p;

            while ( (p = strstr( mp[i].url, "&amp;" )) != NULL )
                strcpy( (char *)p + 1, p + 5 ); /* "&amp;" を "&" へ置換*/

            d.m_title   = mp[i].title;
            d.m_url     = mp[i].url;
            d.m_comment = mp[i].comment;
            d.m_tags    = mp[i].tags;
            d.m_enableToBackward = (i == 0) ? false : true;
            d.m_backToPrevious   = false;

            if ( i > 0 ) {
                int j = i - 1;
                while ( (j >= 0) && deleted[j] )
                    j--;
                if ( j < 0 )
                    d.m_enableToBackward = false;
            }

            int r = d.DoModal();
            if ( r == IDCANCEL )
                break;
            if ( d.m_backToPrevious ) {
                int j = i;
                while ( (--i > 0) && deleted[i] )
                    ;
                if ( deleted[i] == FALSE ) {
                    i--;
                    continue;
                }
                i = j;
            }
            if ( d.m_executeWithoutQuery == true ) {
                title.LoadString(IDS_TTL_DELETE_ALL);
                text.LoadString( IDS_TXT_DELETE_ALL);
                r = MessageBox( NULL,
                                text,   // 残りのブックマークを全部一気に削除してしまっても構わないですね?
                                title,  // ブックマーク一括削除確認
                                MB_YESNO|MB_ICONQUESTION );
                if ( r == IDYES )
                    withQuery = false;
            }
            if ( d.m_execute == false )
                continue;

            pdlg->ShowWindow( SW_SHOWNORMAL );
        }

        text.LoadString(IDS_TXT_CONTINUE_DELETING);
        pdlg->ChangeDialogText( m_bmName,
                                text ); // ブックマーク削除中 ……

        switch ( m_bmType ) {
        case BK_MM_MEMO:
            ret = deleteEntryOnMMmemo( cookie, &(mp[i]) );
            break;
        case BK_DRECOM_RSS:
            ret = deleteEntryOnDrecomRSS( cookie, &(mp[i]) );
            break;
        case BK_FLOG:
            ret = deleteEntryOnFlog( cookie, &(mp[i]) );
            break;
        case BK_LIVEDOOR_CLIP:
            ret = deleteEntryOnLivedoorClip( cookie, &(mp[i]) );
            if ( ret == FALSE ) {
                if ( m_apiKey.GetLength() > 0 )
                    ret = deleteEntryOnLivedoorClip2(
                                username, m_apiKey, mp[i].url );
            }
            break;
        case BK_ECNAVI_CLIP:
            ret = deleteEntryOnEcNaviClip( cookie, &(mp[i]) );
            break;
        case BK_NIFTY_CLIP:
            ret = deleteEntryOnNiftyClip( cookie, &(mp[i]) );
            break;
        case BK_POOKMARK:
            ret = deleteEntryOnPookmark( cookie, &(mp[i]) );
            break;
        case BK_JOLTMARK:
            ret = deleteEntryOnJoltMark( cookie, &(mp[i]) );
            break;
        case BK_BLOGPET:
            ret = deleteEntryOnBlogPet( cookie, &(mp[i]) );
            break;
        case BK_FC2BOOKMARK:
            ret = deleteEntryOnFC2bookmark( cookie, &(mp[i]) );
            break;
        case BK_YJ_BOOKMARK:
            ret = deleteEntryOnYJbookmark( cookie, &(mp[i]) );
            break;
        case BK_YAHOO_BOOKMARKS:
            ret = deleteEntryOnYahooBookmarks( cookie, &(mp[i]) );
            break;
        default:
            ret = FALSE;
            break;
        }

        if ( ret == FALSE ) {
            int r;

            title.LoadString(IDS_TTL_FAILURE_DELETE_BOOKMARKS);
            text.LoadString( IDS_TXT_FAILURE_DELETE_BOOKMARKS);
            r = MessageBox( NULL,
                            text,   // ブックマークの削除に失敗しました    \r\n処理を続行しますか?
                            title,  // ブックマーク削除失敗
                            MB_YESNO|MB_ICONWARNING );
            if ( r == IDYES )
                continue;
            break;
        }
        deleted[i] = TRUE;
    }

    delete [] deleted;
    free( mp );
    if ( !dlg )
        delete pdlg;
}

void    CUserInfo::DeleteBookmarks( bool deleteAll, bool deleteInteractive )
{
    if ( (deleteAll == false) && (deleteInteractive == false) )
        return;

    char                    username2[MAX_USERIDLEN + 1];
    char                    password2[MAX_PASSWDLEN + 1];
    DeleteBookmarkDialog3   dlg3;
    ProceedingDialog        dlg;

    dlg.Create( IDD_PROCEEDING_DIALOG );

    dlg3.m_username = "";
    dlg3.m_password = "";
    username2[0]    = NUL;
    password2[0]    = NUL;

    if ( (m_bmType != BK_NIFTY_CLIP) || (m_apiKey.GetLength() == 0) ) {
        if ( m_bmType != BK_LOCAL_OPML ) {
            GetUserInfo( dlg3.m_username,
                         dlg3.m_password,
                         dlg3.m_targetBookmark );

            if ( m_bmType != BK_1470NET ) {
                int ret = dlg3.DoModal();
                if ( (ret == IDCANCEL)                  ||
                     (dlg3.m_username.GetLength() == 0) ||
                     (dlg3.m_password.GetLength() == 0)    )
                    return;
            }
            else {
                if ( dlg3.m_username.GetLength() == 0 ) {
                    if ( m_username.GetLength() == 0 ) {
                        SettingDialog   sdlg;
                        sdlg.m_1470net = true;
                        sdlg.DoModal();

                        m_authType = sdlg.m_dlg08.m_authType;
                        m_username = sdlg.m_dlg08.m_username;
                        m_password = sdlg.m_dlg08.m_password;
                    }
                    dlg3.m_username = m_username;
                    dlg3.m_password = m_password;
                    if ( (dlg3.m_username.GetLength() == 0) ||
                         (dlg3.m_password.GetLength() == 0)    )
                        return;
                }
            }

            if ( (m_authType == AK_HATENA)         ||
                 (m_authType == AK_TYPEKEY_HATENA) ||
                 (m_authType == AK_HATENA_TYPEKEY)    ) {
                CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
                strcpy( username2, pp->m_hatena.m_username );
                strcpy( password2, pp->m_hatena.m_password );
            }
            else if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
                CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
                strcpy( username2, pp->m_yjBookmark.m_username );
                strcpy( password2, pp->m_yjBookmark.m_password );
                pp->MakeProxyText();
            }
        }
    }

    switch ( m_bmType ) {
    case BK_HATENA:
        DeleteHetanaBookmark( dlg3.m_username, dlg3.m_password,
                              deleteAll ? false : true,
                              &dlg );
        break;

    case BK_DELICIOUS:
        DeleteDeliciousBookmark( dlg3.m_username, dlg3.m_password,
                                 deleteAll ? false : true,
                                 &dlg );
        break;

    case BK_BLUEDOT:
        DeleteBlueDotBookmark( dlg3.m_username, dlg3.m_password,
                               deleteAll ? false : true,
                               &dlg );
        break;

    case BK_NIFTY_CLIP:
        if ( m_apiKey.GetLength() > 0 ) {
            DeleteNiftyClip( m_apiKey,
                             deleteAll ? false : true,
                             &dlg );
            break;
        }
     /* else               */
     /*      fall into ... */
    case BK_MM_MEMO:
    case BK_DRECOM_RSS:
    case BK_FLOG:
    case BK_LIVEDOOR_CLIP:
    case BK_ECNAVI_CLIP:
    case BK_POOKMARK:
    case BK_JOLTMARK:
    case BK_BLOGPET:
    case BK_FC2BOOKMARK:
    case BK_YJ_BOOKMARK:
    case BK_YAHOO_BOOKMARKS:
        DeleteBookmarks( dlg3.m_username, dlg3.m_password,
                         username2, password2,
                         m_authType,
                         deleteAll ? false : true,
                         &dlg );
        break;

    case BK_1470NET:
        Delete1470net( dlg3.m_username, dlg3.m_password,
                       username2, password2,
                       m_authType,
                       deleteAll ? false : true,
                       &dlg );
        break;

    case BK_NEWSING:
    case BK_DIGG:
        break;

    case BK_DIIGO:
        DeleteDiigo( dlg3.m_username, dlg3.m_password,
                     deleteAll ? false : true,
                     &dlg );
        break;

    case BK_LOCAL_OPML:
        DeleteLocalOpml( m_opmlFilename,
                         deleteAll ? false : true,
                         &dlg );
        break;
    }
}


// ブックマークの登録
typedef struct param_sub    {
    // ブックマーク登録スレッドに渡す引数構造体
    int         bookmarkKind;
    RBuser_t    u;
    int         numOfBookmarks;
    MyClip      *myBookmark;
    char        *title;
    int         changeCode;
    FILE        *fp;
}   RBSparam_t;

UINT
RegisterBookmarkSub( LPVOID pParam )
{
    // ブックマーク登録スレッド
    UINT        ret = 0;
    RBSparam_t  *p  = (RBSparam_t *)pParam;
    CString     str1;
    CString     str2;
    CString     str3;

    SetUserAgent( str1, str2, str3 );   /* User-Agent を一時的に変更 */

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_HATENA:
        // はてなブックマークに登録
        putHB( p->u.username, p->u.password,
               p->u.useMyTitle,
               p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DELICIOUS:
        // del.icio.us に登録
        putDelicious( p->u.username, p->u.password,
                      p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_MM_MEMO:
        // MM/Memo に登録
        putMMmemo( p->u.username, p->u.password,
                   p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DRECOM_RSS:
        // ドリコムRSS に登録
        putDrecomRSS( p->u.username, p->u.password,
                      p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_FLOG:
        // Flog に登録
        putFlog( p->u.username, p->u.password,
                 p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP:
        // livedoorクリップ に登録
        putLivedoorClip( p->u.username, p->u.password,
                         p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_ECNAVI_CLIP:
        // Buzzurl に登録
        putEcNaviClip( p->u.username,  p->u.password,
                       p->u.username2, p->u.password2,
                       p->u.authType,
                       p->u.useMyTitle,
                       p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_NIFTY_CLIP:
        // ニフティクリップ に登録
        putNiftyClip( p->u.username, p->u.password,
                      p->u.apiKey,
                      p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_1470NET:
        // 1470.netリニューアル版 に登録
        put1470net( p->u.username,  p->u.password,
                    p->u.username2, p->u.password2,
                    p->u.authType,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_NEWSING:
        // newsing に登録
        putNewsing( p->u.username,  p->u.password,
                    p->u.username2, p->u.password2,
                    p->u.authType,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_POOKMARK:
        // POOKMARK に登録
        putPookmark( p->u.username, p->u.password,
                     p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_BLUEDOT:
        // Blue Dot に登録
        putBlueDot( p->u.username, p->u.password,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_JOLTMARK:
        // JoltMark に登録
        putJoltMark( p->u.username, p->u.password,
                     p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_BLOGPET:
        // BlogPet 気になる記事 に登録
        putBlogPet( p->u.username, p->u.password,
                    p->u.useMyTitle,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_FC2BOOKMARK:
        // FC2BOOKMARK に登録
        putFC2Bookmark( p->u.username, p->u.password,
                        p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_TWITTER:
        // Twitter で発言
        putTwitter( p->u.username, p->u.password,
                    p->u.apiKey,   p->u.secret,
                    p->u.authType,
                    str1, str2, str3,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_TIMELOG:
        // Timelog で発言
        putTimelog( p->u.username, p->u.password,
                    str1, str2, str3,
                    p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_YJ_BOOKMARK:
        // Yahoo! ブックマーク に登録
        putYJbookmark( p->u.username, p->u.password,
                       p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_YAHOO_BOOKMARKS:
        // Yahoo! Bookmarks に登録
        putYahooBookmarks( p->u.username, p->u.password,
                           p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DIGG:
        // digg に登録
        putDigg( p->u.username, p->u.password,
                 p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_TUMBLR:
        // tumblr に投稿
        putTumblr( p->u.username, p->u.password,
                   p->u.blogID,
                   str1,
                   p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_DIIGO:
        // Diigo に投稿
        putDiigo( p->u.username, p->u.password,
                  p->myBookmark, p->numOfBookmarks );
        break;

    case CUserInfo::BK_LOCAL_OPML:
        // ローカルOPMLファイルに登録
        putLocalOpml( p->u.filename, p->myBookmark, p->numOfBookmarks );
        break;
    }

    SetUserAgent( FALSE );  /* User-Agent を元に戻す */
    return ( ret );
}

void    CUserInfo::PutBookmarks(
            const MyClip     *myBookmark,
            int              numOfMyBookmarks,
            const char       *username,
            const char       *password,
            ProceedingDialog *pDlg )
{
    RBSparam_t  param;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = numOfMyBookmarks;
    param.myBookmark = (MyClip *)
                            malloc( sizeof ( MyClip ) * numOfMyBookmarks );
    if ( !param.myBookmark ) {
        CString title;
        CString text;

        title.LoadString(IDS_TTL_MEMORY_EXHAUSTED);
        text.LoadString( IDS_TXT_MEMORY_EXHAUSTED);
        MessageBox( NULL,
                    text,   // 作業に必要なメモリが確保できませんでした。
                    title,  // メモリ確保失敗
                    MB_OK|MB_ICONWARNING );
        return;
    }

    param.u.isTarget   = m_isTarget;
    param.u.useMyTitle = m_useMyTitle;
    strcpy( param.u.username, username );
    strcpy( param.u.password, password );
    param.u.authType = m_authType;
    if ( (m_authType == AK_HATENA)         ||
         (m_authType == AK_TYPEKEY_HATENA) ||
         (m_authType == AK_HATENA_TYPEKEY)    ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_hatena.m_username );
        strcpy( param.u.password2, pp->m_hatena.m_password );
    }
    else if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_yjBookmark.m_username );
        strcpy( param.u.password2, pp->m_yjBookmark.m_password );
        pp->MakeProxyText();
    }
    else {
        param.u.username2[0] = NUL;
        param.u.password2[0] = NUL;
    }
    if ( m_opmlFilename.GetLength() > 0 )
        strcpy( param.u.filename, m_opmlFilename );
    else
        param.u.filename[0] = NUL;

    if ( m_apiKey.GetLength() > 0 )
        strcpy( param.u.apiKey, m_apiKey );
    else
        param.u.apiKey[0] = NUL;

    if ( m_secret.GetLength() > 0 )
        strcpy( param.u.secret, m_secret );
    else
        param.u.secret[0] = NUL;

    if ( m_blogID.GetLength() > 0 )
        strcpy( param.u.blogID, m_blogID );
    else
        param.u.blogID[0] = NUL;

    memcpy( param.myBookmark, myBookmark,
            sizeof ( MyClip ) * numOfMyBookmarks );

    param.title      = NULL;
    param.changeCode = UTF8;
    param.fp         = NULL;

    // ブックマーク登録スレッドを起動
    CWinThread  *tp = AfxBeginThread( RegisterBookmarkSub,
                                      (void *)&param );
    if ( tp ) {
        DWORD   exitCode  = 0;
        int     status;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        // ブックマーク登録スレッドが終了するのを待つ
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView もしくは CBookeyDlg の再描画
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog の再描画
                pDlg->SetFocus();
                pDlg->UpdateWindow();
                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        delete tp;
    }

    free( param.myBookmark );
}

void    CUserInfo::PutBookmarks(
            const MyClip     *myBookmark,
            ProceedingDialog *pDlg,
            bool             useOrigText /* = false */ )
{
    char    txt[BUFSIZ];
    CString title;
    CString text;

    if ( useOrigText == false ) {
        title.LoadString(IDS_TTL_CONTINUE_PUTTING_BOOKMARKS);
        text.LoadString( IDS_TXT_CONTINUE_PUTTING_BOOKMARKS);
        sprintf( txt, text, (const char *)m_bmName );
        pDlg->ChangeDialogText( title,  // ブックマーク登録中
                                txt );
    }

    PutBookmarks( myBookmark, 1,
                  (const char *)m_username, (const char *)m_password,
                  pDlg );
}

void    CUserInfo::PutBookmarks(
            const MyClip *myBookmark,
            int          numOfMyBookmarks,
            const char   *username /* = NULL */,
            const char   *password /* = NULL */ )
{
    CWaitCursor         cur;    // マウスカーソルを砂時計表示
    ProceedingDialog    dlg;
    CString             text;

    text.LoadString(IDS_TXT_CONTINUE_PUTTING_BOOKMARK_INFO);
    dlg.Create( IDD_PROCEEDING_DIALOG );
    dlg.ChangeDialogText( m_bmName,
                          text );   // ブックマーク情報登録中 ……

    if ( !username && !password ) {
        username = (const char *)m_username;
        password = (const char *)m_password;
    }

    PutBookmarks( myBookmark, numOfMyBookmarks,
                  username, password,
                  &dlg );
}


UINT
RegisterBookmarkFromFile( LPVOID pParam )
{
    // ブックマーク情報出力スレッド
    UINT        ret = 0;
    RBSparam_t  *p  = (RBSparam_t *)pParam;
    const char  *s  = "generated by Bookey";

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_LOCAL_OPML:
        outputOPML( p->myBookmark, p->numOfBookmarks,
                    p->title && p->title[0] ? p->title : s,
                    p->changeCode, p->fp );
        break;

    case CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1:
        outputBookmarkHtml( p->myBookmark, p->numOfBookmarks,
                            p->title && p->title[0] ? p->title : s,
                            p->changeCode, p->fp );
        break;

    case CUserInfo::BK_OPERA6_ADR:
        outputOpera6Adr( p->myBookmark, p->numOfBookmarks,
                         p->title && p->title[0] ? p->title : s,
                         p->changeCode, p->fp );
        break;

    case CUserInfo::BK_HATENA_BOOKMARK_ATOM:
        break;

    case CUserInfo::BK_DELICIOUS_XML:
        outputDeliciousXML( p->myBookmark, p->numOfBookmarks, p->fp,
                            p->u.username );
        break;
    }

    return ( ret );
}

void    CUserInfo::PutBookmarks(
            const MyClip *myBookmark,
            int          numOfMyBookmarks,
            const char   *bookmarkNameAsImport,
            bool         &result )
{
    CFileDialog *fileDlg = NULL;
    FILE        *fp      = NULL;
    CString     fileName;
    CString     fileType;
    const char  *fileExtention;
    const char  *fileDefault;
    CString     title;
    CString     text;
    RBSparam_t  param;

    fileExtention = NULL;
    fileDefault   = NULL;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = numOfMyBookmarks;
    param.myBookmark = (MyClip *)
                            malloc( sizeof ( MyClip ) * numOfMyBookmarks );
    if ( !param.myBookmark ) {
        title.LoadString(IDS_TTL_MEMORY_EXHAUSTED);
        text.LoadString( IDS_TXT_MEMORY_EXHAUSTED);
        MessageBox( NULL,
                    text,   // 作業に必要なメモリが確保できませんでした。
                    title,  // メモリ確保失敗
                    MB_OK|MB_ICONWARNING );
        return;
    }

    param.u.isTarget     = m_isTarget;
    param.u.authType     = m_authType;
    param.u.username[0]  = NUL;
    param.u.password[0]  = NUL;
    param.u.username2[0] = NUL;
    param.u.password2[0] = NUL;
    param.u.filename[0]  = NUL;

    memcpy( param.myBookmark, myBookmark,
            sizeof ( MyClip ) * numOfMyBookmarks );

    param.title      = NULL;
    param.changeCode = UTF8;
    param.fp         = NULL;

    result   = false;
    fileName = _T("");

    switch ( m_bmType ) {
    case BK_LOCAL_OPML:
        fileType.LoadString( IDS_FILETYPE_OPML );
        title.LoadString(IDS_WRFAIL_OPML);
        text.LoadString( IDS_OPFAIL_OPML);
        fileExtention = "opml";
        break;

    case BK_NETSCAPE_BOOKMARK_FILE_1:
        fileType.LoadString( IDS_FILETYPE_HTML );
        title.LoadString(IDS_WRFAIL_HTML);
        text.LoadString( IDS_OPFAIL_HTML);
        fileExtention = "html";
        break;

    case BK_OPERA6_ADR:
        fileType.LoadString( IDS_FILETYPE_OPERA_6 );
        title.LoadString(IDS_WRFAIL_ADR);
        text.LoadString( IDS_OPFAIL_ADR);
        fileExtention = "adr";
        break;

    case BK_HATENA_BOOKMARK_ATOM:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_WRFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        break;

    case BK_DELICIOUS_XML:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_WRFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        break;
    }

    if ( fileExtention )
        fileDlg = new CFileDialog( FALSE, fileExtention, fileDefault,
                                   OFN_OVERWRITEPROMPT,
                                   fileType );
    if ( fileDlg ) {
        if ( fileDlg->DoModal() == IDOK )
            fileName = fileDlg->GetPathName();
        delete fileDlg;

        if ( fileName.GetLength() > 0 ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            if ( pp->m_langCode == 0x0411 ) {
                // 日本語モードの場合のみ
                if ( m_bmType == BK_NETSCAPE_BOOKMARK_FILE_1 ) {
                    int r = ::MessageBox( NULL,
                                "UTF-8 で出力しますか? \r\n\r\n"
                                "「いいえ」をクリックすると Shift_JIS で出力"
                                "します。    \r\nInternet Explorer へのイン"
                                "ポートをお考えの場合は\r\n「いいえ」を選択"
                                "してください",
                                "文字コード確認",
                                MB_YESNO|MB_ICONQUESTION );
                    if ( r == IDNO )
                        param.changeCode = SJIS;
                }
            }
            fp = fopen( fileName, "w" );
        }
    }

    if ( fp ) {
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        ProceedingDialog    dlg;
        const char          *s;

        text.LoadString(IDS_TXT_CONTINUE_PUTTING_BOOKMARK_INFO);
        dlg.Create( IDD_PROCEEDING_DIALOG );
        dlg.ChangeDialogText( m_bmName,
                              text );   // ブックマーク情報登録中

        if ( param.changeCode != SJIS )
            param.changeCode = GetChangeCode( bookmarkNameAsImport );
        param.fp = fp;
        s = param.changeCode != UTF8 ? bookmarkNameAsImport
                                     : sjis2utf(bookmarkNameAsImport);
        if ( s ) {
            param.title = (char *)malloc( strlen( s ) + 1 );
            if ( param.title )
                strcpy( param.title, s );
        }

        if ( m_bmType == BK_DELICIOUS_XML ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            if ( pp->m_delicious.m_username.GetLength() > 0 )
                strcpy( param.u.username, pp->m_delicious.m_username );
        }

        // ブックマーク情報出力スレッドを起動
        CWinThread  *tp = AfxBeginThread( RegisterBookmarkFromFile,
                                          (void *)&param );
        if ( tp ) {
            DWORD   exitCode  = 0;
            int     status;
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            // ブックマーク情報出力スレッドが終了するのを待つ
            tp->m_bAutoDelete = FALSE;
            do {
                status = GetExitCodeThread( tp->m_hThread, &exitCode );
                if ( status == FALSE )
                    break;
                if ( exitCode == STILL_ACTIVE ) {
                    // CBookeyView もしくは CBookeyDlg の再描画
                    MSG msg;
                    if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                        DispatchMessage( &msg );

                    // ProceedingDialog の再描画
                    dlg.SetFocus();
                    dlg.UpdateWindow();
                    Sleep( MS_THREAD_REGISTERBOOKMARK );
                }
            } while ( exitCode == STILL_ACTIVE );

            delete tp;
        }

        if ( param.title )
            free( param.title );
        fclose( fp );
        result = true;
    }
    else {
        switch ( m_bmType ) {
        case BK_LOCAL_OPML:
        case BK_NETSCAPE_BOOKMARK_FILE_1:
        case BK_OPERA6_ADR:
        case BK_HATENA_BOOKMARK_ATOM:
        case BK_DELICIOUS_XML:
            ::MessageBox( NULL, text, title, MB_OK|MB_ICONWARNING );
            break;
        }
    }

    free( param.myBookmark );
}


// ブックマークの取得
typedef struct param_sub2   {
    // ブックマーク取得スレッドに渡す引数構造体
    int                 bookmarkKind;
    char                bookmarkName[32];
    char                dialogText[96];
    RBuser_t            u;
    int                 numOfBookmarks;
    MyClip              *myBookmark;
    ProceedingDialog    *dlg;
    FILE                *fp;
    size_t              fileSize;
}   IBSparam_t;

UINT
InquiryBookmarkSub( LPVOID pParam )
{
    // ブックマーク取得スレッド
    UINT        ret   = 0;
    IBSparam_t  *p    = (IBSparam_t *)pParam;
    int         total = 0;

    SetUserAgent( TRUE );   /* User-Agent を一時的に変更 */

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_HATENA:
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        total = getNumberOfHatenaBookmark( p->u.username, p->u.password );
        p->myBookmark = getHB( p->u.username, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_DELICIOUS:
        // del.icio.us からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        total = getNumberOfBookmarksOnDelicious( p->u.username, p->u.password );
        p->numOfBookmarks = total;
        p->myBookmark = getDelicious( p->u.username, p->u.password,
                                      &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_MM_MEMO:
        // MM/Memo からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getMMmemo( p->u.username, p->u.password,
                                   &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_DRECOM_RSS:
        // ドリコムRSS からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getDrecomRSS( p->u.username, p->u.password,
                                      &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_FLOG:
        // Flog からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        if ( p->u.password[0] )
            p->myBookmark = getFlog( p->u.username, p->u.password, NULL,
                                     &(p->numOfBookmarks) );
        else
            p->myBookmark = getFlog( NULL, NULL, p->u.username,
                                     &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP:
        // livedoorクリップ からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getLivedoorClip( p->u.username, p->u.password,
                                         &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_ECNAVI_CLIP:
        // Buzzurl からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        if ( p->u.password[0]                              ||
             ((p->u.authType == AK_YAHOOJAPAN_BBAUTH) &&
              (p->u.password2[0])                        )    ) {
            CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
            pp->MakeProxyText();
            p->myBookmark = getEcNaviClip( p->u.username,  p->u.password,
                                           p->u.username2, p->u.password2,
                                           p->u.authType,
                                           NULL,
                                           &total, &(p->numOfBookmarks) );
        }
        else
            p->myBookmark = getEcNaviClip( NULL, NULL,
                                           NULL, NULL,
                                           AK_ORIGINAL,
                                           p->u.username,
                                           &(p->numOfBookmarks), &total );
        break;

    case CUserInfo::BK_NIFTY_CLIP:
        // ニフティクリップ からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getNiftyClip( p->u.username, p->u.password,
                                      p->u.apiKey,
                                      &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_1470NET:
        // 1470.netリニューアル版 からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = get1470net( p->u.username,  p->u.password,
                                    p->u.username2, p->u.password2,
                                    p->u.authType,
                                    &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_NEWSING:
    case CUserInfo::BK_DIGG:
        break;

    case CUserInfo::BK_POOKMARK:
        // POOKMARK Airlines からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getPookmark( p->u.username, p->u.password,
                                     &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_BLUEDOT:
        // Blue Dot からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        total = getNumberOfBookmarksOnBlueDot( p->u.username, p->u.password );
        p->numOfBookmarks = total;
        p->myBookmark = getBlueDot( p->u.username, p->u.password,
                                    &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_JOLTMARK:
        // JoltMark からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getJoltMark( p->u.username, p->u.password,
                                     &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_BLOGPET:
        // BlogPet 気になる記事 からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getBlogPet( p->u.username, p->u.password,
                                    &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_FC2BOOKMARK:
        // FC2BOOKMARK からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getFC2Bookmark( p->u.username, p->u.password,
                                        &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_YJ_BOOKMARK:
        // Yahoo! ブックマーク からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getYJbookmark( p->u.username, p->u.password,
                                       &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_YAHOO_BOOKMARKS:
        // Yahoo! Bookmarks からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getYahooBookmarks( p->u.username, p->u.password,
                                           &total, &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_DIIGO:
        // Diigo からブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getDiigo( p->u.username, p->u.password,
                                  &(p->numOfBookmarks) );
        break;

    case CUserInfo::BK_LOCAL_OPML:
        // ローカルOPMLファイルからブックマーク情報を取得
        p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );
        p->myBookmark = getLocalOpml( p->u.filename, &(p->numOfBookmarks) );
        break;
    }

    if ( (total > 0) && (p->numOfBookmarks < total) ) {
        // 取得失敗
        char        msg[BUFSIZ];
        CString     title;
        CString     text;
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();

        title.LoadString(IDS_TTL_FAILURE_GET_BOOKMARK_INFO);
        text.LoadString( IDS_TXT_FAILURE_GET_BOOKMARK_INFO);

        if ( pp->m_langCode != 0x0411 )
            sprintf( msg,
                     text,  // Only %d in %d all was able to be acquired.
                     p->numOfBookmarks, total );
        else
            sprintf( msg,
                     text,  // 全 %d 件中 %d 件しか取得できませんでした。
                     total, p->numOfBookmarks );
        if ( p->numOfBookmarks == 0 ) {
            unsigned short status = getStatusCode();
            if ( status >= 400 )
                sprintf( msg + strlen(msg), "\r\n(status code: %d)", status );
        }
        MessageBox( NULL,
                    msg,
                    title,  // ブックマーク情報取得失敗
                    MB_OK|MB_ICONWARNING );
        if ( p->numOfBookmarks < total / 10 ) { /* {@@} */
            free( p->myBookmark );
            p->myBookmark = NULL;
            p->numOfBookmarks = 0;
        }                                       /* {@@} */
    }

#ifdef  _DEBUG
    if ( p->myBookmark && (p->numOfBookmarks > 0) )
        dumpBookmark( p->bookmarkKind, p->myBookmark, p->numOfBookmarks );
#endif

    SetUserAgent( FALSE );  /* User-Agent を元に戻す */
    return ( ret );
}

MyClip  *CUserInfo::GetBookmarks(
            int        &numOfMyBookmarks,
            const char *username /* = NULL */,
            const char *password /* = NULL */ )
{
    IBSparam_t          param;
    MyClip              *p = NULL;
    ProceedingDialog    dlg;
    CWaitCursor         cur;    // マウスカーソルを砂時計表示
    CString             text;

    dlg.Create( IDD_PROCEEDING_DIALOG );

    numOfMyBookmarks = 0;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = 0;
    param.myBookmark     = NULL;
    param.dlg            = &dlg;
    param.fp             = NULL;
    strcpy( param.bookmarkName, (const char *)m_bmName );
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    strcpy( param.dialogText,
            text ); // ブックマーク情報取得中 ……

    switch ( m_bmType ) {
    case BK_HATENA:
        if ( !username || !strcmp( username, m_username ) ) {
            strcpy( param.u.username, m_username );
            strcpy( param.u.password, m_password );
        }
        else {
            strcpy( param.u.username, username );
            param.u.password[0] = NUL;
        }
        break;

    case BK_MM_MEMO:
    case BK_1470NET:
    case BK_DELICIOUS:
    case BK_FLOG:
    case BK_ECNAVI_CLIP:
    case BK_LIVEDOOR_CLIP:
    case BK_NIFTY_CLIP:
    case BK_NEWSING:
    case BK_POOKMARK:
    case BK_BLUEDOT:
    case BK_JOLTMARK:
    case BK_BLOGPET:
    case BK_FC2BOOKMARK:
    case BK_YJ_BOOKMARK:
    case BK_YAHOO_BOOKMARKS:
    case BK_DIGG:
    case BK_DIIGO:
        if ( username && *username ) {
            strcpy( param.u.username, username );
            if ( password && *password )
                strcpy( param.u.password, password );
            else
                param.u.password[0] = NUL;
        }
        else {
            strcpy( param.u.username, m_username );
            strcpy( param.u.password, m_password );
        }
        break;

    case BK_DRECOM_RSS:
        if ( (username && *username) && (password && *password) ) {
            strcpy( param.u.username, username );
            strcpy( param.u.password, password );
        }
        else {
            strcpy( param.u.username, m_username );
            strcpy( param.u.password, m_password );
        }
        break;

    case BK_LOCAL_OPML:
    case BK_NETSCAPE_BOOKMARK_FILE_1:
    case BK_OPERA6_ADR:
    case BK_DELICIOUS_XML:
        param.u.username[0] = NUL;
        param.u.password[0] = NUL;
        break;
    }
    param.u.authType = m_authType;
    if ( (m_authType == AK_HATENA)         ||
         (m_authType == AK_TYPEKEY_HATENA) ||
         (m_authType == AK_HATENA_TYPEKEY)    ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_hatena.m_username );
        strcpy( param.u.password2, pp->m_hatena.m_password );
    }
    else if ( m_authType == AK_YAHOOJAPAN_BBAUTH ) {
        CBookeyApp  *pp = (CBookeyApp *)AfxGetApp();
        strcpy( param.u.username2, pp->m_yjBookmark.m_username );
        strcpy( param.u.password2, pp->m_yjBookmark.m_password );
        pp->MakeProxyText();
    }
    else {
        param.u.username2[0] = NUL;
        param.u.password2[0] = NUL;
    }
    if ( m_opmlFilename.GetLength() > 0 )
        strcpy( param.u.filename, m_opmlFilename );
    else
        param.u.filename[0] = NUL;

    if ( m_apiKey.GetLength() > 0 )
        strcpy( param.u.apiKey, m_apiKey );
    else
        param.u.apiKey[0] = NUL;

    if ( m_secret.GetLength() > 0 )
        strcpy( param.u.secret, m_secret );
    else
        param.u.secret[0] = NUL;

    // ブックマーク取得スレッドを起動
    CWinThread  *tp = AfxBeginThread( InquiryBookmarkSub,
                                      (void *)&param );
    if ( tp ) {
        DWORD   exitCode  = 0;
        int     status;
        CWaitCursor cur;    // マウスカーソルを砂時計表示

        // ブックマーク取得スレッドが終了するのを待つ
        tp->m_bAutoDelete = FALSE;
        do {
            status = GetExitCodeThread( tp->m_hThread, &exitCode );
            if ( status == FALSE )
                break;
            if ( exitCode == STILL_ACTIVE ) {
                // CBookeyView もしくは CBookeyDlg の再描画
                MSG msg;
                if ( PeekMessage( &msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE ) )
                    DispatchMessage( &msg );

                // ProceedingDialog の再描画
                dlg.SetFocus();
                dlg.UpdateWindow();
                Sleep( MS_THREAD_REGISTERBOOKMARK );
            }
        } while ( exitCode == STILL_ACTIVE );

        if ( param.myBookmark ) {
            if ( param.numOfBookmarks > 0 ) {
                p = param.myBookmark;
                numOfMyBookmarks = param.numOfBookmarks;
            }
            else
                free( param.myBookmark );
        }

        delete tp;
    }

    return ( p );
}


UINT
InquiryBookmarkFromFile( LPVOID pParam )
{
    // ブックマーク取得スレッド
    UINT        ret = 0;
    IBSparam_t  *p  = (IBSparam_t *)pParam;

    p->dlg->ChangeDialogText( p->bookmarkName, p->dialogText );

    switch ( p->bookmarkKind ) {
    case CUserInfo::BK_LOCAL_OPML:
        p->myBookmark = inputOPML( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_NETSCAPE_BOOKMARK_FILE_1:
        p->myBookmark = inputBookmarkHtml( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_OPERA6_ADR:
        p->myBookmark = inputOpera6Adr( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_HATENA_BOOKMARK_ATOM:
        p->myBookmark = inputHatenaFeed( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_LIVEDOOR_CLIP_RSS:
        p->myBookmark = inputLivedoorFeed( &(p->numOfBookmarks), p->fp );
        break;

    case CUserInfo::BK_DELICIOUS_XML:
        p->myBookmark = inputDeliciousXML( &(p->numOfBookmarks),
                                           p->fp, p->fileSize );
        break;
    }

    return ( ret );
}

MyClip  *CUserInfo::GetBookmarks(
            int  &numOfMyBookmarks,
            bool &result )
{
    IBSparam_t          param;
    CString             fileName;
    CString             fileType;
    const char          *fileExtention;
    const char          *fileDefault;
    CString             title;
    CString             text;
    ProceedingDialog    dlg;
    MyClip              *p         = NULL;
    CFileDialog         *fileDlg   = NULL;
    FILE                *fp        = NULL;
    int                 numOfClips = 0;

    result        = false;
    fileName      = _T("");
    fileType      = _T("");
    fileExtention = NULL;
    fileDefault   = NULL;

    param.bookmarkKind   = m_bmType;
    param.numOfBookmarks = 0;
    param.myBookmark     = NULL;
    param.dlg            = &dlg;
    param.fp             = NULL;
    param.fileSize       = 0;
    strcpy( param.bookmarkName, (const char *)m_bmName );
    text.LoadString(IDS_TXT_CONTINUE_GETTING_BOOKMARKS);
    strcpy( param.dialogText,
            text ); // ブックマーク情報取得中 ……
    param.u.username[0]  = NUL;
    param.u.password[0]  = NUL;
    param.u.username2[0] = NUL;
    param.u.password2[0] = NUL;
    param.u.authType     = m_authType;
    param.u.filename[0]  = NUL;

    switch ( m_bmType ) {
    case BK_LOCAL_OPML:
        fileType.LoadString( IDS_FILETYPE_OPML );
        title.LoadString(IDS_RDFAIL_OPML);
        text.LoadString( IDS_OPFAIL_OPML);
        fileExtention = "opml";
        break;

    case BK_NETSCAPE_BOOKMARK_FILE_1:
        fileType.LoadString( IDS_FILETYPE_HTML );
        title.LoadString(IDS_RDFAIL_HTML);
        text.LoadString( IDS_OPFAIL_HTML);
        fileExtention = "html";
        break;

    case BK_OPERA6_ADR:
        fileType.LoadString( IDS_FILETYPE_OPERA_6 );
        title.LoadString(IDS_RDFAIL_ADR);
        text.LoadString( IDS_OPFAIL_ADR);
        fileExtention = "adr";
        fileDefault   = "opera6.adr";
        break;

    case BK_HATENA_BOOKMARK_ATOM:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_RDFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        fileDefault   = "dump.xml";
        break;

    case BK_LIVEDOOR_CLIP_RSS:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_RDFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        fileDefault   = "export.xml";
        break;

    case BK_DELICIOUS_XML:
        fileType.LoadString( IDS_FILETYPE_XML );
        title.LoadString(IDS_RDFAIL_XML);
        text.LoadString( IDS_OPFAIL_XML);
        fileExtention = "xml";
        fileDefault   = "all.xml";
        break;
    }

    if ( fileExtention )
        fileDlg = new CFileDialog( TRUE, fileExtention, fileDefault,
                                   OFN_FILEMUSTEXIST | OFN_READONLY,
                                   fileType );
    if ( fileDlg ) {
        if ( fileDlg->DoModal() == IDOK )
            fileName = fileDlg->GetPathName();
        delete fileDlg;

        if ( fileName.GetLength() > 0 ) {
            struct stat s;
            if ( !stat( fileName, &s ) )
                param.fileSize = s.st_size;
            fp = fopen( fileName, "rb" );
        }
    }

    if ( fp ) {
        dlg.Create( IDD_PROCEEDING_DIALOG );
        param.fp = fp;

        // ブックマーク取得スレッドを起動
        CWinThread  *tp = AfxBeginThread( InquiryBookmarkFromFile,
                                          (void *)&param );
        if ( tp ) {
            DWORD   exitCode  = 0;
            int     status;
            CWaitCursor cur;    // マウスカーソルを砂時計表示

            // ブックマーク取得スレッドが終了するのを待つ
            tp->m_bAutoDelete = FALSE;
            do {
                status = GetExitCodeThread( tp->m_hThread, &exitCode );
                if ( status == FALSE )
                    break;
                if ( exitCode == STILL_ACTIVE ) {
                    // CBookeyView もしくは CBookeyDlg の再描画
                    MSG msg;
                    if ( PeekMessage(&msg, 0, WM_PAINT, WM_PAINT, PM_REMOVE) )
                        DispatchMessage( &msg );

                    // ProceedingDialog の再描画
                    dlg.SetFocus();
                    dlg.UpdateWindow();
                    Sleep( MS_THREAD_REGISTERBOOKMARK );
                }
            } while ( exitCode == STILL_ACTIVE );

            if ( param.myBookmark ) {
                if ( param.numOfBookmarks > 0 ) {
                    p = param.myBookmark;
                    numOfClips = param.numOfBookmarks;
                }
                else
                    free( param.myBookmark );
            }

            delete tp;
        }
        fclose( fp );
        result = true;
    }
    else {
        switch ( m_bmType ) {
        case BK_LOCAL_OPML:
        case BK_NETSCAPE_BOOKMARK_FILE_1:
        case BK_OPERA6_ADR:
        case BK_HATENA_BOOKMARK_ATOM:
        case BK_LIVEDOOR_CLIP_RSS:
        case BK_DELICIOUS_XML:
            ::MessageBox( NULL, text, title, MB_OK|MB_ICONWARNING );
            break;
        }
    }

    numOfMyBookmarks = numOfClips;

    return ( p );
}


/* タグ一覧の取得 */
TagList *CUserInfo::GetTagList( int &numOfTags )
{
    TagList *p = NULL;

    numOfTags = 0;
    switch ( m_bmType ) {
    case BK_DELICIOUS:
        p = getTagListOnDelicious( m_username, m_password, &numOfTags );
        break;

    case BK_BLUEDOT:
        p = getTagListOnBlueDot( m_username, m_password, &numOfTags );
        break;

    case BK_HATENA:
        p = getTagListOnHatenaBookmark( m_username, m_password, &numOfTags );
        break;

    case BK_NIFTY_CLIP:
        p = getTagListOnNiftyClip( m_username, m_password, &numOfTags );
        break;
    }

    return ( p );
}

/* タグの削除 */
void    CUserInfo::DeleteTag( const char *tag )
{
    switch ( m_bmType ) {
    case BK_DELICIOUS:
        removeTagOnDelicious( m_username, m_password, tag );
        break;

    case BK_HATENA:
        removeTagFromBookmarksOnHatena( m_username, m_password, tag );
        break;

    case BK_NIFTY_CLIP:
        removeTagFromBookmarksOnNiftyClip( m_username, m_password, tag );
        break;
    }
}

/* タグの置換 */
void    CUserInfo::ReplaceTag( const char *oldTag, const char *newTag )
{
    switch ( m_bmType ) {
    case BK_DELICIOUS:
        renameTagOnDelicious( m_username, m_password, oldTag, newTag );
        break;

    case BK_BLUEDOT:
        renameTagOnBlueDot( m_username, m_password, oldTag, newTag );
        break;

    case BK_HATENA:
        renameTagFromBookmarksOnHatena( m_username, m_password,
                                        oldTag, newTag );
        break;

    case BK_NIFTY_CLIP:
        renameTagFromBookmarksOnNiftyClip( m_username, m_password,
                                           oldTag, newTag );
        break;
    }
}


/*
 *  初期設定ファイル関連
 */

bool    CUserInfo::EvalKeys(
                        const char          *p,
                        const unsigned char *rsaString )
{
    bool    ret = false;
    char    target[BUFSIZ];
    char    encrypted[BUFSIZ];

    encrypted[0] = NUL;

    sprintf( target, "bookmarkFor%s", m_bmSymbol );
    if ( evalKey( p, target, m_isTarget ) )
        ret = true;
    if ( ret == false ) {
        sprintf( target, "useMyTitleFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_useMyTitle ) )
            ret = true;
    }
    if ( ret == false ) {
        long    l = 0;

        sprintf( target, "authTypeFor%s", m_bmSymbol );
        if ( evalKey( p, target, l ) ) {
            ret = true;
            m_authType = (AUTH_TYPE)l;
        }
    }
    if ( ret == false ) {
        sprintf( target, "usernameFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_username ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "passwordFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_password,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "filenameFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_opmlFilename ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "APIkeyFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_apiKey,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "SecretFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            extractKey( m_secret,
                        (unsigned char *)encrypted,
                        (unsigned char *)rsaString );
            ret = true;
        }
    }
    if ( ret == false ) {
        sprintf( target, "blogIDFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_blogID ) )
            ret = true;
    }
    if ( ret == false ) {
        sprintf( target, "blogNameFor%s", m_bmSymbol );
        if ( evalKey( p, target, m_blogName ) )
            ret = true;
    }

    return ( ret );
}

bool    CUserInfo::CheckKeys(
                        const char          *p,
                        const unsigned char *rsaString,
                        bool                &ret )
{
    bool    cont = false;
    char    encrypted[BUFSIZ];
    char    target[BUFSIZ];
    bool    checkPassword = true;
    bool    checkApiKey   = true;
    bool    checkSecret   = true;

    sprintf( target, "passwordFor%sEncrypted", m_bmSymbol );
    if ( evalKey( p, target, encrypted ) ) {
        checkKey( m_password,
                  (unsigned char *)encrypted,
                  rsaString,
                  checkPassword );
        cont = true;
    }

    if ( cont == false ) {
        sprintf( target, "APIkeyFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_apiKey,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkApiKey );
            cont = true;
        }
    }

    if ( cont == false ) {
        sprintf( target, "SecretFor%sEncrypted", m_bmSymbol );
        if ( evalKey( p, target, encrypted ) ) {
            checkKey( m_secret,
                      (unsigned char *)encrypted,
                      rsaString,
                      checkSecret );
            cont = true;
        }
    }

    ret &= (checkPassword & checkApiKey & checkSecret);

    return ( cont );
}

void    CUserInfo::WriteKeys(
            FILE          *fp,      // (I/O) 書き出し先
            char          *key,     // (I)   公開鍵
            unsigned char **secret, // (I/O) 復号に必要な情報(秘密鍵)
            bool          &done )   // (O)   暗号化処理実行済みか否か
{
    char    target[BUFSIZ];

    sprintf( target, "bookmarkFor%s", m_bmSymbol );
    writeKey( fp, target, m_isTarget );

    sprintf( target, "useMyTitleFor%s", m_bmSymbol );
    writeKey( fp, target, m_useMyTitle );

    sprintf( target, "authTypeFor%s", m_bmSymbol );
    writeKey( fp, target, (long)m_authType );

    if ( m_username.GetLength() > 0 ) {
        sprintf( target, "usernameFor%s", m_bmSymbol );
        writeKey( fp, target, m_username );
    }

    if ( m_password.GetLength() > 0 ) {
        sprintf( target, "passwordFor%s", m_bmSymbol );
        writeKey( fp, target, m_password, key, secret, done );
    }

    if ( m_opmlFilename.GetLength() > 0 ) {
        sprintf( target, "filenameFor%s", m_bmSymbol );
        writeKey( fp, target, m_opmlFilename );
    }

    if ( m_apiKey.GetLength() > 0 ) {
        sprintf( target, "APIkeyFor%s", m_bmSymbol );
        writeKey( fp, target, m_apiKey, key, secret, done );
    }

    if ( m_secret.GetLength() > 0 ) {
        sprintf( target, "SecretFor%s", m_bmSymbol );
        writeKey( fp, target, m_secret, key, secret, done );
    }

    if ( m_blogID.GetLength() > 0 ) {
        sprintf( target, "blogIDFor%s", m_bmSymbol );
        writeKey( fp, target, m_blogID );
    }
    if ( m_blogName.GetLength() > 0 ) {
        sprintf( target, "blogNameFor%s", m_bmSymbol );
        writeKey( fp, target, m_blogName );
    }
}


/* ブックマーク出力(エクスポート)時の入力(インポート)側の文字コードを取得 */
int CUserInfo::GetChangeCode( CString bookmarkNameAsImport )
{
    int         changeCode = UTF8;

    if ( m_tgt_hatenaBookmark.GetLength() == 0 ) {
        m_tgt_hatenaBookmark.LoadString( IDS_TGT_HATENA_BOOKMARK );
        m_tgt_delicious.LoadString( IDS_TGT_DELICIOUS );
        m_tgt_mmMemo.LoadString( IDS_TGT_MMMEMO );
        m_tgt_drecomRSS.LoadString( IDS_TGT_DRECOM_RSS );
        m_tgt_flog.LoadString( IDS_TGT_FLOG );
        m_tgt_livedoorClip.LoadString( IDS_TGT_LIVEDOOR_CLIP );
        m_tgt_ecNaviClip.LoadString( IDS_TGT_ECNAVI_CLIP );
        m_tgt_niftyClip.LoadString( IDS_TGT_NIFTY_CLIP );
        m_tgt_1470net.LoadString( IDS_TGT_1470NET );
        m_tgt_pookmark.LoadString( IDS_TGT_POOKMARK );
        m_tgt_blueDot.LoadString( IDS_TGT_BLUEDOT );
        m_tgt_joltMark.LoadString( IDS_TGT_JOLTMARK );
        m_tgt_blogPet.LoadString( IDS_TGT_BLOGPET );
        m_tgt_fc2bookmark.LoadString( IDS_TGT_FC2_BOOKMARK );
        m_tgt_yjBookmark.LoadString( IDS_TGT_YJ_BOOKMARK );
        m_tgt_yahooBookmarks.LoadString( IDS_TGT_YAHOO_BOOKMARKS );
        m_tgt_diigo.LoadString( IDS_TGT_DIIGO );
        m_tgt_hatenaFeed.LoadString( IDS_TGT_HATENA_FEED );
        m_tgt_deliciousXML.LoadString( IDS_TGT_DELICIOUS_XML );
    }

    if ( !bookmarkNameAsImport.Compare( m_tgt_mmMemo ) )
        changeCode = EUC2UTF;
    else if ( !bookmarkNameAsImport.Compare( m_tgt_hatenaBookmark ) ||
              !bookmarkNameAsImport.Compare( m_tgt_delicious )      ||
              !bookmarkNameAsImport.Compare( m_tgt_blueDot )        ||
              !bookmarkNameAsImport.Compare( m_tgt_drecomRSS )      ||
              !bookmarkNameAsImport.Compare( m_tgt_flog )           ||
              !bookmarkNameAsImport.Compare( m_tgt_livedoorClip )   ||
              !bookmarkNameAsImport.Compare( m_tgt_ecNaviClip )     ||
              !bookmarkNameAsImport.Compare( m_tgt_niftyClip )      ||
              !bookmarkNameAsImport.Compare( m_tgt_1470net )        ||
              !bookmarkNameAsImport.Compare( m_tgt_pookmark )       ||
              !bookmarkNameAsImport.Compare( m_tgt_joltMark )       ||
              !bookmarkNameAsImport.Compare( m_tgt_blogPet )        ||
              !bookmarkNameAsImport.Compare( m_tgt_fc2bookmark )    ||
              !bookmarkNameAsImport.Compare( m_tgt_yjBookmark )     ||
              !bookmarkNameAsImport.Compare( m_tgt_yahooBookmarks ) ||
              !bookmarkNameAsImport.Compare( m_tgt_diigo )          ||
              !bookmarkNameAsImport.Compare( m_tgt_hatenaFeed )     ||
              !bookmarkNameAsImport.Compare( m_tgt_deliciousXML )      )
        changeCode = SJIS2UTF; /* bookey内部でShift_jis変換済みの場合を含む */

    return ( changeCode );
}


void CUserInfo::PutBookmarks(
            bool         force,
            const MyClip *myBookmark,
            int          numOfMyBookmarks,
            const char   *username /* = NULL */,
            const char   *password /* = NULL */
        )
{
    CUserInfo   u = *this;

    u = force;
    u.PutBookmarks( myBookmark, numOfMyBookmarks,
                     (const char *)username,
                     (const char *)password );
}
