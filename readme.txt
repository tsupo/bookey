bookey -- ソーシャルブックマーク管理ツール
  作者: tsupo (H.Tsujimura,  mailto: tsupo@na.rim.or.jp)
  パッケージ作成日: 2009年6月22日
  パッケージ版数:   0.63c

  このパッケージの説明:

    このパッケージには、以下のファイルが含まれています。

      readme.txt      いま、あなたが読んでいるファイル
      bookey.exe      ソーシャルブックマーク管理ツール 本体
      xmlRPC.dll      上記のプログラムを動かすのに必要なモジュール (サーバとの通信用)
      iconv.dll       同上 (文字コードの変換用) [このファイルの配布は GNU LGPL に従います]

      bookey.exe.manifest
                      bookey.exe を Windows XP 以降で動かす場合に参照するファイル
                      (ただし、Windows をクラシック設定にしている場合は、Windows XP 以降の
                       場合でも参照されません)

      get1470net.exe    1470.net リニューアル版 からエクスポートするツール
      getBlogPet.exe    Blogpet 気になる記事 からエクスポートするツール
      getBlueDot.exe    Blue Dot からエクスポートするツール
      getBuzzurl.exe    Buzzurl からエクスポートするツール
      getDelicious.exe  del.icio.us からエクスポートするツール
      getDRC.exe        ドリコムRSS の Clip! からエクスポートするツール
      getFlogexe        Flog からエクスポートするツール
      getHB.exe         はてなブックマーク からエクスポートするツール
      getJoltMark.exe   JoltMark からエクスポートするツール
      getLC.exe         livedoorクリップ からエクスポートするツール
      getMMmemo.exe     MM/Memo からエクスポートするツール
      getNC.exe         ニフティクリップ からエクスポートするツール
      getPookmark.exe   POOKMARK Airlines からエクスポートするツール
      put1470net.exe    1470.net リニューアル版 へインポートするツール
      putBlogPet.exe    Blogpet 気になる記事  へインポートするツール
      putBlueDot.exe    Blue Dot へインポートするツール
      putBuzzurl.exe    Buzzurl へインポートするツール
      putDRC.exe        ドリコムRSS の Clip! へインポートするツール
      putDelicious.exe  del.icio.us へインポートするツール
      putFlog.exe       Flog へインポートするツール
      putHB.exe         はてなブックマーク へインポートするツール
      putJoltMark.exe   JoltMark へインポートするツール
      putLC.exe         livedoorクリップ へインポートするツール
      putMMmemo.exe     MM/Memo へインポートするツール
      putNC.exe         ニフティクリップ へインポートするツール
      putNewsing.exe    newsing へインポートするツール
      putPookmark.exe   POOKMARK Airlines へインポートするツール

      iconv-1.9.1.win32 以下のファイル
        Windows 用 の GNU iconv ライブラリ のバイナリパッケージ
        (GNU LIBRARY GENERAL PUBLIC LICENSE に基づく配布です)
      src 以下のファイル
        ソーシャルブックマーク管理ツールのソース

  背景:
    はてなブックマーク や del.icio.us といったソーシャルブックマークは使ってみるといろいろ
    便利なのですが、バックアップを取ったり、あるソーシャルブックマークの内容を別のソーシャ
    ルブックマークに移したりするのは、ブックマークの数が少ないうちはまだいいのですが、ブッ
    クマークの数が増えてくると、手作業でやるにはあまりにも大変です。幸いなことに、はてなブッ
    クマークも del.icio.us もブックマークを管理するのに利用できる API が用意されているされ
    ているので、手軽にソーシャルブックマークを管理できるツールを作ってみました。

  配布条件:
    iconv.dll および iconv-1.9.1.win32 以下のファイル は、GNU LIBRARY GENERAL PUBLIC LICENSE
    にしたがいます。
    それ以外のファイル(bookey.exe, get1470net.exe, getBlogPet.exe, getBlueDot.exe,
    getBuzzurl.exe, getDRC.exe, getDelicious.exe, getFlog.exe, getHB.exe, getJoltMark.exe,
    getLC.exe, getMMmemo.exe, getNC.exe, getPookmark.exe, put1470net.exe, putBlogPet.exe,
    putBlueDot.exe, putBuzzurl.exe, putDRC.exe, putDelicious.exe, putFlog.exe, putHB.exe,
    putJoltMark.exe, putLC.exe, putMMmemo.exe, putNC.exe, putNewsing.exe, putPookmark.exe,
    xmlRPC.dll, および ドキュメント)は、tsupo の著作物です。
    配布は自由としますが、プログラムの動作および動作に伴い発生する諸々の事象に関しては無保証
    とします。

    xmlRPC.dll に関しては、私(tsupo)の作成・配布している他のソフトウェアのパッケージにも含ま
    れていることがありますが、他のパッケージに含まれているものではなく、bookey.exe のパッケー
    ジに含まれているものをお使いください。(xmlRPC.dll のバージョンアップは結構頻繁に行なって
    いるため、同梱のもの以外を使用すると不整合が起きる可能性があります。)

    なお、SSL および RSA暗号化処理を組み込むにあたり、xmlRPC.dll に OpenSSL のスタティックラ
    イブラリを組み込んでいます。OpenSSL については http://www.openssl.org/ を参照してくださ
    い。また、OpenSSL のライセンスに関しては http://www.openssl.org/contrib/ を参照してくだ
    さい。

    ※ ブックマーク投稿(登録)ダイアログで表示するタグ候補の選定処理で、Yahoo! Japan の「形態
       素解析API」を利用しています。
         http://developer.yahoo.co.jp/webapi/jlp/ma/v1/parse.html
         http://developer.yahoo.co.jp/start/ (Yahoo!デベロッパーネットワークの「利用ガイド」)

    書籍、雑誌等で本ツールの紹介を行なったり、本パッケージを収録したりする場合は、事前に連絡
    してください。

  動作環境:
    Windows 95,98,98SE,ME (Windows 95A 以降、できれば Windows 95 OSR2.0 以降推奨)
    Windows NT4.0SP6a, 2000, XP, Vista
    Windows Server 2000, Windows 2003 Server
    (proxy 経由で使う場合は、Internet Explorer 5.0 以降、Firefox 1.0.5 以降、Opera 7.0 以降
     の少なくともどれか1つがインストール済みであることを推奨)
   ※ パーソナルファイアウォールやアンチウィルスソフトを使用している場合は、別途、ファイア
      ウォールの調整、アンチウィルスソフトの設定変更が必要な場合があります。
   ※ 本ツールはインターネットに接続されている状態で使用します。

  インストール:
    本アーカイブに収録されている bookey.exe, getBlogPet.exe, getBlueDot.exe, getBuzzurl.exe,
    getDRC.exe, getDelicious.exe, getFlog.exe, getHB.exe, getJoltMark.exe, getLC.exe,
    getMMmemo.exe, getNC.exe, getPookmark.exe, put1470net.exe, putBlogPet.exe,
    putBlueDot.exe, putBuzzurl.exe, putDRC.exe, putDelicious.exe, putFlog.exe, putHB.exe,
    putJoltMark.exe, putLC.exe, putMMmemo.exe, putNC.exe, putNewsing.exe, putPookmark.exe,
    xmlRPC.dll, iconv.dll を同一のディレクトリ(フォルダ)に解凍し、ご利用ください。
    特に、それ以外に必要な作業はありません。

  アンインストール:
    bookey.exe, get1470net.exe, getBlogPet.exe, getBlueDot.exe, getBuzzurl.exe,
    getDRC.exe, getDelicious.exe, getFlog.exe, getHB.exe, getJoltMark.exe, getLC.exe,
    getMMmemo.exe, getNC.exe, getPookmark.exe, put1470net.exe, putBlogPet.exe,
    putBlueDot.exe, putBuzzurl.exe, putDRC.exe, putDelicious.exe, putFlog.exe,
    putHB.exe, putJoltMark.exe, putLC.exe, putMMmemo.exe, putNC.exe, putNewsing.exe,
    putPookmark.exe, xmlRPC.dll, iconv.dll, bookey.inf を削除するだけです。
    レジストリはいじっていません。
    なお、bookey.inf は、bookey.exe が自動生成する設定ファイルです。

  使い方:
    bookey.exe ブックマーク管理ツール
      アイコンをダブルクリック、または、DOSプロンプトから bookey [Enter] で起動します。

      (1) ブックマーク登録機能
      Internet Explorer または Firefox のアドレス欄(閲覧中の web ページのURL が表示されている
      ところ)のアイコン(Favicon)をマウスでドラッグし、bookey のメイン画面にドロップすると、そ
      の web ページをはてなブックマーク, del.icio.us, MM/Memo, BlogPeople Tags, ドリコムRSS
      (のClip!), Flog, livedoorクリップ, Buzzurl, ニフティクリップ, 1470.netリニューアル版, 
      newsing, POOKMARK Airlines, Blue Dot, JoltMark, BlogPet 気になる記事, FC2BOOKMARK, Yahoo!
      ブックマーク(yahoo.co.jp), Yahoo! Bookmarks (yahoo.com), Diigo のどれか1つ以上に同時に
      登録することができます。ドロップ後、その web ページに関する情報を入力するダイアログが出
      ますので、コメントやタグを入力してください。

      タグはスペース(空白文字)区切りで入力してください。

      Opera をお使いの方は、アドレス欄をドラッグし、いったんデスクトップにドラッグし、インター
      ネットショートカット(ファイル)を作成してください。その後、そのショートカットをドロップ
      し、bookey のメイン画面にドロップすることで、ブックマークの登録を行なうことができます。

      また、ブラウザの「お気に入り」もドラッグ・アンド・ドロップにより、取り込むことができま
      す。あるいは、ブラウザやエディタ等で表示されている URL をクリップボードにコピーした後、
      bookey のメイン画面にペーストすることで、その URL のWebページをブックマークすることも
      できます。2ちゃんねる等でよく見かける ttp:// 表記のものも取り込めます。

      さらに、ブックマークしようとしている Web ページが「はてなアカウント Auto-discovery」に
      対応していれば、その Webページのオーナーに対し、はてなポイントを送信することもできます。
      ただし、はてなポイントを送信するには、自身がはてなのアカウントを持っている必要があります。

      ブックマークしようとしているページがアマゾンの個別詳細ページあるいは「はてなダイアリー」
      の(アマゾンの)商品の紹介ページであれば、はてなブックマークの「コレクション」にも追加す
      ることができます。アマゾンのスポーツストアのように URL に asin という文字列を含まない商
      品詳細ページも可能な限り、コレクションに追加できるようにしてみました。1470.netリニュー
      アル版の MONO にも登録できます。

      ブックマーク登録対象に、ドリコムRSS(のClip!) もしくは Flog が含まれる場合は、カテゴリ、
      ジャンル(ドリコムRSS ではフォルダと呼んでいる)をプルダウンメニューで指定することができ
      ます。プルダウンメニューで指定したカテゴリ、ジャンルは、他のブックマークにはタグとして
      流用されます(ただし、現時点では、ドリコムRSS のフォルダは、MyClip! からの移行時に自動
      設定されたものにのみ対応しています。ユーザが別途新規に作成したフォルダには未対応です)。

      0.21版から livedoor クリップ、ニフティクリップ、POOKMARK Airlines の3つに関して、公開・
      非公開を選択して登録できるようになりました。0.30版から、FC2BOOKMARK についても、公開・
      非公開を選択して登録できるようになりました。0.32版から、Yahoo! ブックマークの公開・非公
      開にも対応しています。0.56版から del.icio.us の private saving (非公開での投稿)にも対応
      しました。

      5段階評価に対応しているソーシャルブックマーク(MM/Memo、1470.netリニューアル版、BlogPeople
      Tags、livedoor Bookmark)に関して、評価付きで登録できます。また、newsing に関して、○×
      評価付きで登録することができます(○×の評価をしない場合は、newsing への登録は行ないま
      せん。newsing に登録したい場合のみ、○×評価を行なってください。なお、5段階評価につい
      ては「評価なし」のままでも評価対応ソーシャルブックマークに登録できます)。

      Blue Dot への登録は del.icio.us 互換 API を利用しているため、評価付き(5段階評価)での登
      録や、画像付きでの登録はできません。また、公開範囲の指定(Everyone, Friends, Private)の
      指定もできません(常に Everyone になります)。なお、「BlogPet ブックマーク」はブックマー
      クしていること自体と、ブックマークコメントの両方を独立に公開範囲指定できますが、bookey
      では両者に同じ公開レベルを設定します(一般公開、友達に公開、非公開の3レベルが選択可能)。

      0.18版から、ローカルPC上の OPML ファイルにもブックマークを残せるようにしました。オンラ
      インブックマークサービスのバックアップとして、ご利用ください。

      0.31版から「何をブックマークしたか」を Twitter に投稿(報告)できるようになりました。
      0.35版から Timelog にも投稿(報告)できるようになりました。

      0.37版から digg への投稿にも対応しました。ただし、digg に投稿するときは、digg 専用の入
      力ダイアログを併用します(digg に投稿するときは CAPTCHA の入力が必要になることがあるため)。

      0.41版から、「はてなスター」に投票する(☆をつける)機能をつけました。「はてなスター」は、
      一種のブックマーク機能を兼ねています。ブックマーク登録・編集ダイアログで、「はてなスター」
      アイコンをクリックした回数だけ、☆をつけることができます。

      0.52版から tumblr への投稿(link形式)にも対応しました。
      0.62版から同一アカウントで複数の tumblr を開設している人向けに、primary (メインの tumblr)
      以外の tumbleblog を投稿先として選択できるようにしました。設定ダイアログで選択先を指定す
      ることができます。

      (2) ブックマーク管理機能(インポート、エクスポート、同期、削除)
      メイン画面の「ブックマーク管理ツールを起動する」ボタンを押すと、ブックマーク管理画面が
      立ち上がります。ブックマークの取得(各ブックマークサービスからのエクスポート、bookey へ
      のインポート)、登録(bookey からのエクスポート、各ブックマークサービスへのインポート)、
      削除、同期を行なうことができます。

        ・ブックマークの取得
           はてなブックマーク、del.icio.us、BlogPeople IB (インスタントブックマーク)、
           BlogPeople Tags, MM/Memo, Flog, ドリコムRSS(のClip!)、livedoorクリップ, Buzzurl、ニ
           フティクリップ、1470.netリニューアル版、POOKMARK Airlines, Blue Dot, JoltMark,
           BlogPet 気になる記事、FC2BOOKMARK, Yahoo! ブックマーク、Yahoo! Bookmarks、Diigo お
           よび OPML ファイルの内容を取り込みます。
           なお、はてなブックマーク(プライベートモードのものを除く)と BlogPeople Tags、Flog,
           Buzzurl、ニフティクリップ, livedoorクリップ, POOKMARK Airlines、Blue Dot,JoltMark,
           FC2BOOKMARK, Yahoo! ブックマーク に関しては、ID(ユーザ名)がわかっている人ならどの人
           のブックマークでも(プライベートに設定されているものを除く全てのブックマーク[Blue Dot
           の場合は公開範囲が Every One に設定されている全てのブックマーク]が)取得可能です(Flog
           の場合は、ユーザ名ではなく、ユーザ各人に割り当てられている数字(ID)を指定します。Buzzurl
           の場合は記者名、ニフティクリップの場合はクリップのスクリーンネーム(@nifty ID や PLEASY
           ID とは独立に設定できます)を指定します)。「BlogPet 気になる記事」に関しては、プロフィー
           ルページの URL の末尾にある(ハッシュコード化された32桁の)IDを指定することで、当該ユー
           ザの「一般公開」されているブックマークを取得することができます(自分自身のブックマーク
           を取得するときは自分のユーザ名とパスワードを指定してください)。
           注意: BlogPeople IB の内容を取得するときは BlogPeople のユーザ名(メールアドレス)を
           使用しますが、BlogPeople Tags の内容を取得するときは、ブックマーク用に別途設定した
           ユーザ名を用います(自分のブックマークを取得するときは、メールアドレスを指定しても構
           いませんが、その場合はパスワードも指定する必要があります)。
           livedoorクリップ、ニフティクリップ、POOKMARK Airlines、FC2BOOKMARK, Yahoo! ブックマー
           ク については、ログイン時に使用するユーザ名 (ニフティクリップの場合は @nifty ID また
           は PLEASY ID、POOKMARK Airlines の場合は Jugem Key ID、FC2BOOKMARK の場合はメールア
           ドレス) とパスワードを同時に指定することで、プライベートモードに設定されているクリッ
           プも取得できます。

           0.19版から、ブラウザ(Firefox, Internet Explorer, Opera など)のブックマーク(お気に入
           り)をエクスポートしたファイル(NETSCAPE互換のhtmlファイル[NETSCAPE-Bookmark-file-1形
           式のファイル])を読み込むことができるようになりました。また、Opera 独自の形式のブック
           マークファイル(opera6.adr)も読み込むことができます。del.icio.us や POOKMARK Airlines
           からエクスポートしたhtmlファイルも NETSCAPE-Bookmark-file-1形式互換(ただし、タグの情
           報を格納できるように仕様が拡張されています)ですので、取り込むことが可能です。はてな
           ブックマークから html 形式でエクスポートしたファイルも(NETSCAPE-Bookmark-file-1形式
           なので)取り込めます。さらに、はてなブックマークから RSS 1.0 あるいは Atom 0.3 フィー
           ド形式でエクスポートしたファイルも取り込むことができます。

           0.21版から livedoor クリップからエクスポートしたファイル(RSS 2.0形式)も読み込むこと
           ができるようになりました。

           0.32版から del.icio.us の
               http://del.icio.us/api/posts/all
           にブラウザ等でアクセスし、取得・保存した XML ファイルも読み込むことができるようにな
           りました。

        ・ブックマークの登録
           「ブックマークの取得」で取り込んだブックマークを、はてなブックマーク、del.icio.us、
           MM/Memo、BlogPeople Tags、ドリコムRSS(のClip!)、Flog、livedoor クリップ、Buzzurl、
           ニフティクリップ、1470.netリニューアル版、POOKMARK Airlines, Blue Dot, JoltMark, 
           BlogPet 気になる記事, FC2BOOKMARK, Yahoo! ブックマーク、Yahoo! Bookmarks、Diigo 
           に登録したり、OPMLファイルに書き出したりします。
           注意: BlogPeople Tags に登録するときは、ブックマーク用に別途取得したユーザ名では
           なく、BlogPeople にログインするときのメールアドレスを使用します。

           0.19版から、NETSCAPE-Bookmark-file-1形式互換の html ファイルや opera6.adr に準拠
           した形式のファイルとしても出力することができるようになりました。この形式で出力し
           ておけば、ブラウザのお気に入り(ブックマーク)にインポートすることが可能です。

           0.32版から del.icio.us の posts/all で取得・保存した XML ファイルと同じ形式でも
           出力できるようになりました。この形式で出力しておくと、
             http://bookmarks.yahoo.co.jp/settings/data/deliciousimport
           の『「del.icio.us」からのインポート』を利用してインポートすることができます。

        ・ブックマークの同期
           はてなブックマーク、del.icio.us、MM/Memo、BlogPeople Tags, ドリコムRSS(のClip!)、
           Flog、livedoorクリップ、Buzzurl、ニフティクリップ、1470.netリニューアル版、
           POOKMARK Airlines, Blue Dot, JoltMark, BlogPet 気になる記事、FC2BOOKMARK, Yahoo!
           ブックマーク、Yahoo! Bookmarks、Diigo のうち任意の二者間でブックマーク内容の同期
           を取ります。例えば、はてなブックマークには登録済みだが del.icio.us には未登録な
           ブックマークを del.icio.us に登録したり、del.icio.us には登録済みだがはてなブック
           マークには未登録なブックマークをはてなブックマークに登録したりすることができます。
           ローカルPC上に保存されている OPML ファイルと、各オンラインブックマークとの間での同
           期を取ることもできます。

        ・ブックマークの削除
           はてなブックマーク、del.icio.us、BlogPeople Tags、MM/Memo, Flog、livedoorクリップ、
           ニフティクリップ、Buzzurl、1470.netリニューアル版、ドリコムRSS(のClip!)、POOKMARK
           Airlines, Blue Dot, JoltMark, BlogPet 気になる記事、FC2BOOKMARK, Yahoo! ブックマー
           ク、Yahoo! Bookmarks に登録済みのブックマークを一気に全部削除したり、ブックマーク
           を1個ずつ表示させながら削除したいブックマークを対話的に指定したりすることができます。
           ローカルPC上に保存されている OPML ファイルから任意のブックマークを削除することもで
           きます。

        ・タグの置換
          はてなブックマーク、del.icio.us, ニフティクリップ, Blue Dot に登録済みの記事に付け
          たタグの中からタグを1つ選択し、全記事を対象にそのタグを別のタグに一括置換すること
          ができます。

        ・タグの削除
          はてなブックマーク、del.icio.us, ニフティクリップ に登録済みの記事に付けたタグの中
          からタグを1つ選択し、全記事を対象にそのタグだけを一括削除することができます。


      なお、本ツールによる各種設定内容は bookey.inf という名前のファイルに保存されます。いった
      ん設定を完全にクリアしたい場合は、bookey.inf を削除した後、本ツールを起動してください。

      0.25版から、日本語版以外の言語版の Windows で本ツールを起動した場合は、メッセージを全て
      英語で表示するようにしました。たぶん、英語が native な人にはおかしいと感じられる表現が
      あると思いますが、気付いた方は指摘、連絡していただけるとうれしいです。

      イントラネット内など、proxy サーバ経由でインターネットに接続する場合は、Internet Explorer、
      Firefox、Opera の proxy の設定を順に参照し、必要な情報を取得します。これらのブラウザの少
      なくとも1つがインストール済みで proxy 設定を行なっている場合は、特に本ツール独自の proxy
      設定を行なう必要はありません。これらのブラウザをインストールしていない場合は、proxy.txt
      という名前のファイルを用意し、bookey.exe のあるディレクトリに配置してください。proxy.txt
      には以下の内容を記述してください(Firefox で複数profileを使い分ける運用をしている人で、
      各profile毎に別のproxyサーバを使う設定を行なっている場合は、proxy.txt を用意して、明示的
      にproxyサーバを指定してください)。

        proxyサーバ名(またはproxyサーバのIPアドレス)
        ポート番号
        proxyサーバアクセス用のユーザ名   (必要な場合のみ)
        proxyサーバアクセス用のパスワード (必要な場合のみ)

        例)
          http://proxy.example.com/
          8080

      0.29c版から、「プロキシサーバ設定」ボタンをメインダイアログに用意しました。このボタンを
      押して、設定を行なえば、proxy.txt を用意する必要はありません。なお、proxy.txt の内容を
      適用して proxyサーバへのアクセスを行なおうとして失敗した場合は、proxy.txt を(bookeyが)
      いったん削除し、その後のインターネットアクセスが発生するタイミングでproxyサーバ設定ダイ
      アログを表示することがあります。

      本ツールの応用例:
        はてなブックマークの内容を取得して OPML ファイルとして書き出したあと、ブックマークの内
        容を全部削除。その後、OPMLファイルの中身をテキストエディタで編集し、編集後の OPML ファ
        イルをはてなブックマークに登録する。


      ・Twitter の OAuth 認証について
         bookey の 0.61版から、Twitter の OAuth 認証に対応しています。OAuth 認証を使うことで、Twitter のアカ
         ウント名、パスワードをアプリケーション(bookey)側で預かる必要がなくなるため、 セキュリティが向上しま
         す。従来の認証方法(BASIC認証)も選択できるようにしてありますので、お好きな方をお使いください。それぞ
         れの認証方法では、以下のような利点、欠点があります。

           OAuth認証 [安全性が高いけど、面倒]
             メリット: 
               - パスワードをアプリケーションに教える必要がありません
               - 通信回線のどこかで何者かにデータを改竄された場合、必ず認証エラーになります
                 [改竄されている可能性があることを検出できます]
                 (ただし、別の原因で認証エラーになった場合と区別できない、という難点もあります) 
             デメリット:
               - 複数の端末 (デスクトップPC、ノートPC、その他) を使う可能性がある場合、いちばん最後に取得し
                 た OAuth アクセストークンのみ有効です(それ以外のアクセストークンはすべて無効になることがあ
                 ります)。
               - 認証エラーが発生したら(= アクセストークンの有効期間が終わったら)、その都度、アクセストーク
                 ンを取得し直す必要があります。
               - (Twitter 特有の問題であると思われますが) しばしば、サーバ側の OAuth 関連処理が更新されるタ
                 イミングで、 長時間(数日間)認証エラーが続く状態になることがあります。 認証エラー状態が長く
                 続く場合は、BASIC認証の方に切り替えてみてください。

           BASIC認証 [安全性は低いけど、簡単、確実]
             メリット:
               - OAuth 認証よりも使用実績が長い/多いため、比較的安定しています。ノウハウも蓄積されています。
               - 複数の端末(デスクトップPC、ノートPC、その他)を使う可能性がある場合でも、特に意識することな
                 く使用できます (アカウント名、パスワードは端末が違っても共通に使えます)
             デメリット:
               - パスワードをアプリケーションに教える必要があります(bookey の設定ファイルには暗号化した状態
                 でパスワードを記録しますので、設定ファイルを第三者に見られても、パスワードがばれることはあ
                 りません)。
               - BASIC認証によるアカウント名、パスワードのエンコードは BASE64 方式 (簡単にデコードできる)な
                 ので、通信回線のどこかで何者かにデータを盗聴された場合、アカウント名、パスワードが漏れてし
                 まいます。

  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=--=-=--=-=--=-=--=-=--=-=-
  (以下のツールは、すべてコマンドライン[コマンドプロンプトあるいはDOS窓]で使用する)
    get1470net.exe        1470.net リニューアル版 からエクスポートするツール

      get1470net [-x] -u TypeKeyユーザ名 -p TypeKeyパスワード
      get1470net [-x] -U はてなID -P はてなパスワード
      get1470net [-x] -a{T|H} -u TypeKeyユーザ名 -p TypeKeyパスワード -U はてなID -P はてなパスワード
        -x: proxy を使う
        -aT: まず TypeKey 認証でのアクセスを試し、失敗した場合ははてな認証でのアクセスを試みる
        -aH: まずはてな認証でのアクセスを試し、失敗した場合は TypeKey 認証でのアクセスを試みる

         1470.net リニューアル版 の内容を OPML ファイル(put*.exe で取り込める)形式で
         標準出力に出力します。

    getBlogPet.exe  BlogPet 気になる記事 からエクスポートするツール

      getBlogPet [-x] [-u BlogPetユーザ名] [-p BlogPetパスワード]
         -x: proxy を使う

         BlogPet 気になる記事 の内容を OPML ファイル(put*.exe で取り込める)形式で
         標準出力に出力します。

    getBlueDot.exe  Blue Dot からエクスポートするツール

      getBlueDot [-x] [-u Blue Dot ユーザ名] [-p Blue Dot パスワード]
         -x: proxy を使う

         Blue Dot の内容を OPML ファイル(put*.exe で取り込める)形式で標準出力に
         出力します。

    getBuzzurl.exe  Buzzurl からエクスポートするツール

      getBuzzurl [-x] [-u メールアドレス] [-p Buzzurlパスワード]
         -x: proxy を使う

         Buzzurl の内容を OPML ファイル(put*.exe で取り込める)形式で標準出力に
         出力します。

    getDelicious.exe  del.icio.us からエクスポートするツール

      getDelicious [-x] [-u del.icio.usユーザ名] [-p del.icio.usパスワード]
         -x: proxy を使う

         del.icio.us の内容を OPML ファイル(put*.exe で取り込める)形式で標準出力
         に出力します。

    getDRC.exe  ドリコムRSS の Clip! (クリップリーダー) からエクスポートするツール

      getDRC [-x] [-u ドリコムアカウントユーザ名] [-p ドリコムアカウントパスワード]
         -x: proxy を使う

         ドリコムRSS の Clip! の内容を OPML ファイル(put*.exe で取り込める)形式で標
         準出力に出力します。

    getFlog.exe  Flog からエクスポートするツール

      getFlog [-x] [-u メールアドレス] [-p Flogパスワード]
         -x: proxy を使う

         Flog の内容を OPML ファイル(put*.exe で取り込める)形式で標準出力に出力し
         ます。

    getHB.exe         はてなブックマーク からエクスポートするツール

      getHB [-x] -u ユーザ名
         -x: proxy を使う

         はてなブックマークの内容を OPML ファイル(put*.exe で取り込める)形式で標
         準出力に出力します。

    getJoltMark.exe  JoltMark からエクスポートするツール

      getBlueDot [-x] [-u JoltMarkユーザ名] [-p JoltMarkパスワード]
         -x: proxy を使う

         JoltMark の内容を OPML ファイル(put*.exe で取り込める)形式で標準出力に
         出力します。

    getLC.exe  livedoor クリップ からエクスポートするツール

      getLC [-x] [-u livedoorユーザ名] [-p livedoorパスワード]
         -x: proxy を使う

         livedoor クリップ の内容を OPML ファイル(put*.exe で取り込める)形式で標
         準出力に出力します。

    getMMmemo.exe     MM/Memo からエクスポートするツール

      getMMmemo [-x] -u TypeKeyユーザ名 -p TypeKeyパスワード
         -x: proxy を使う

         MM/Memo の内容を OPML ファイル(put*.exe で取り込める)形式で標準出力に出
         力します。
         (MM/Memo は TypeKey 認証を利用している)

    getNC.exe  ニフティクリップ からエクスポートするツール

      getNC [-x] [-u ユーザ名] [-p パスワード]
         -x: proxy を使う

         ニフティクリップ の内容を OPML ファイル(put*.exe で取り込める)形式で標
         準出力に出力します。
         ユーザ名とパスワードは @nifty の ID とパスワード、または PLEASY ID と
         そのパスワードのいずれかを指定します。

    getPookmark.exe  POOKMARK Airlines からエクスポートするツール

      getPookmark [-x] [-u JugemKeyID] [-p パスワード]
         -x: proxy を使う

         POOKMARK Airlines の内容を OPML ファイル(put*.exe で取り込める)形式で標
         準出力に出力します。

    put1470net.exe    1470.net リニューアル版 へインポートするツール

      put1470net [-x] -u TypeKeyユーザ名 -p TypeKeyパスワード [-i OPMLファイル名]
      put1470net [-x] -U はてなID -P はてなパスワード [-i OPMLファイル名]
      put1470net [-x] -a{T|H} -u TypeKeyユーザ名 -p TypeKeyパスワード -U はてなID -P はてなパスワード
                 [-i OPMLファイル名]
         -x: proxy を使う
         -aT: まず TypeKey 認証でのアクセスを試し、失敗した場合ははてな認証でのアクセスを試みる
         -aH: まずはてな認証でのアクセスを試し、失敗した場合は TypeKey 認証でのアクセスを試みる
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を 1470.net リニューアル版 に登録します。

    putBlogPet.exe  BlogPet 気になる記事 へインポートするツール

      putBlogPet [-x] [-F] -u BlogPetユーザ名 -p BlogPetパスワード [-i OPMLファイル名]
         -x: proxy を使う
         -F: すでに登録されているタイトルと自分が登録しようとしているタイトルが食い違う
             場合、自分が登録しようとしているタイトルで上書き登録する。
             なお、このオプションを指定しない場合は、すでに登録されているタイトルをその
             まま使用する。
               注意: 「BlogPet 気になる記事」ではタイトルはユーザ全員の共有リソースにな
                     ります。上書き登録するかどうかは各自の慎重な判断で決定してください
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を BlogPet 気になる記事 に登録します。

    putBlueDot.exe  Blue Dot へインポートするツール

      putBlueDot [-x] -u Blue Dot ユーザ名 -p Blue Dot パスワード [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を Blue Dot に登録します。

    putBuzzurl.exe   Buzzurl へインポートするツール

      putBuzzurl [-x] [-F] -u メールアドレス -p Buzzurlパスワード [-i OPMLファイル名]
         -x: proxy を使う
         -F: すでに登録されているタイトルと自分が登録しようとしているタイトルが食い違う
             場合、自分が登録しようとしているタイトルで上書き登録する。
             なお、このオプションを指定しない場合は、すでに登録されているタイトルをその
             まま使用する。
               注意: Buzzurl ではタイトルはユーザ全員の共有リソースになります。上書き登
                     録するかどうかは各自の慎重な判断で決定してください
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を Buzzurl に登録します。

    putDRC.exe       ドリコムRSS の Clip! (クリップリーダー) へインポートするツール

      putDRC [-x] -u ドリコムアカウントユーザ名 -p ドリコムアカウントパスワード
             [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を ドリコムRSS の Clip! に登録します。

    putDelicious.exe  del.icio.us へインポートするツール

      putDelicious [-x] -u del.icio.usユーザ名 -p del.icio.usパスワード
                   [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を del.icio.us に登録します。

    putFlog.exe      Flog へインポートするツール

      putFlog [-x] -u メールアドレス -p Flogパスワード [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を Flog に登録します。

    putHB.exe         はてなブックマーク へインポートするツール

      putHB [-x] [-F] -u はてなID -p はてなパスワード [-i OPMLファイル名]
         -x: proxy を使う
         -F: すでに登録されているタイトルと自分が登録しようとしているタイトルが食い違う
             場合、自分が登録しようとしているタイトルで上書き登録する。
             なお、このオプションを指定しない場合は、すでに登録されているタイトルをその
             まま使用する。
               注意: 「はてなブックマーク」ではタイトルはユーザ全員の共有リソースになり
                     ます。上書き登録するかどうかは各自の慎重な判断で決定してください
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容をはてなブックマークに登録します。

    putJoltMark.exe  JoltMark へインポートするツール

      putJoltMark [-x] -u JoltMarkユーザ名 -p JoltMarkパスワード
                  [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を JoltMark に登録します。

    putLC.exe         livedoorクリップ へインポートするツール

      putLC [-x] -u livedoorユーザ名 -p livedoorパスワード [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を livedoorクリップ に登録します。

    putMMmemo.exe     MM/Memo へインポートするツール

      putMMmemo [-x] -u TypeKey認証用ユーザ名 -p TypeKey認証用パスワード
                [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を MM/Memo に登録します。

    putNC.exe         ニフティクリップ へインポートするツール

      putNC [-x] -u ユーザ名 -p パスワード -i OPMLファイル名
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を ニフティクリップ に登録します。
         ユーザ名とパスワードは @nifty の ID とパスワード、または PLEASY ID と
         そのパスワードのいずれかを指定します。

    putNewsing.exe     newsing へインポートするツール

      putNewsing [-x] -u newsingユーザ名 -p newsingパスワード [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を newsing に登録します。newsing へインポートする場合は
         OPML ファイル中に「○×情報」が必要です。また、コメントの長さが30バイト以下
         の場合は、インポートに失敗することがあります。

    putPookmark.exe     POOKMARK Airlines へインポートするツール

      putPookmark [-x] -u JugemKeyID -p パスワード [-i OPMLファイル名]
         -x: proxy を使う
         -i オプション省略時は標準入力から OPML ファイルを読み込みます

         OPML ファイルの内容を POOKMARK Airlines に登録します。


  わかっている不具合:
    (1) 他のブックマークから MM/Memo への「同期」を行なうとき、「今日」のブックマーク以外は何
        回でも同期しようとしてしまうことがある
          → MM/Memo から取得したブックマーク情報に反映されるまで時間がかかることがあるのが原
             因の模様 (後日、時間をおいて再度試すと、「登録(同期)済み」と正しく判定できる)
          → とりあえず、運用でカバーしてください
    (2) MM/Memo で「登録に失敗しました」ダイアログが表示される場合で、何回かやり直して登録に成功
        した場合、重複登録されていることがある(MM/Memo のサーバの負荷が高いときに発生しやすい)
        → 本当に登録に失敗したのか、「最新」ページを取得、解析して確認する処理を追加することで
           回避可能?
           (1470.net リニューアル版でも同様の現象が発生することがある)
    (3) charset が ISO-2022-JP な OPML からデータをインポートしようとすると、タイトル、コメント、
        タグが文字化けすることがある(bookey 自身が生成する OPML の charset は UTF-8 ですので、
        bookey を使ってエクスポートした OPML を改めてインポートする分には問題は発生しません)

    (4) Buzzurl と newsing の両方を共に Yahoo! Japan ID を使ってアクセスする設定にしている場合、
        どちらか一方へのログイン(認証)が失敗することがあります。この現象が発生した場合、いったん
        bookey を終了し、再起動させてから、まず、どちらか一方のみ Yahoo! Japan ID によるアクセス
        を行なって(ブックマークの登録などを実行して)おき、その後、もう一方も Yahoo! Japan ID に
        よるアクセスを行なうように設定してからアクセスを行なうことで、以後、両方共に Yahoo! Japan
        ID によるアクセスができるようになります。

    (5) Diigo の「ブックマーク削除」処理は、今のところ、常に失敗します。対応策を検討中です。

    (6) 2008年11月25日の「はてなブックマーク」リニューアル以降、一部の API を除き、正常に稼動
        していないようです。そのため、「ブックマークの登録」以外は、期待通りに動かないことが
        あります。API が正常復帰次第、期待通りに動くようになるものと思われます
        → その後、結局、以前とは違う仕様、挙動になってしまった API が多く、可能な限り bookey
           側で、以前と同じ使い方ができるように、差異を吸収するようにしました(吸収しきれていな
           いものもあります)。記事によっては、指定したタイトルで投稿できないことがありますが、
           これは「はてなブックマーク」の仕様(挙動)変更によるもので、bookey 側では対処不可能
           です。あしからず、ご了承ください。

  注意:
    (1) del.icio.us から登録済みの全ブックマークを取得する場合、del.icio.us のサーバが過負荷状
        態だと、取得に失敗することがあります。取得できなかった場合は、時間を置いて、再度試して
        みてください。他のブックマークサービスでも、サーバ側の状況次第で、同様に失敗することが
        あります(経験上、ブックマークサービスの中では del.icio.us で最も取得失敗が発生しやすい
        ようです。一度失敗すると、ある程度時間[30分くらい?]が経過するまでは、常に失敗し続ける
        ようです)。 → 0.55版から、API による取得に失敗した場合は、htmlページのスクレイピングに
        よるブックマークの取得を試みるようにしてみました。

    (2) JoltMark は登録失敗することが多いようです(ここ最近は、登録に成功することの方が少ないで
        す。スパム性の高いブックマークの登録行為増加によるサーバ負荷増大が原因と思われます)。
        Flog も、時間帯によっては、登録失敗が頻発することがあります。

    (3) FC2ブックマークもサーバ負荷が高いときに「ブックマークの登録に失敗しました」ダイアログ
        が表示されることがありますが、登録自体は実際には成功している(登録成功の応答が返ってき
        ていないだけである)こともあります。

    (4) 0.57d 版を最後に、BlogPeople Tags および BlogPeople IB への対応を終了しました。

    (5) ここしばらく、Flog の「管理画面」がおかしい(html の中身が途中で切れている)せいで、Flog
        に登録したブックマークの削除ができない状態になっています。Flog の「管理画面」が復旧する
        までは、削除ができないままとなります。あとで削除が必要になる可能性のあるブックマークの
        登録は控えておいた方がいいでしょう。

  今後の予定:
    (1) ブックマークの登録内容の修正機能のサポート
    (2) Blog it! (ブログに投稿する機能)のサポート

  バグ報告:
    このパッケージに含まれるプログラムの動作異常等、不具合を発見された方は、できるだけ詳細な
    報告を
      tsupo@na.rim.or.jp
    まで、電子メイルにて送付していただけると幸いです。

  サポート情報、1次配布元:
    本パッケージは、以下の URL にて配布しています。
        http://sites.google.com/site/tsujimura543/bookey/archives
    以下の Webページに関連情報があります。
        http://watcher.moe-nifty.com/memo/2005/10/bookey.html
        http://watcher.moe-nifty.com/memo/2005/10/_bookey_004_0017.html
        http://watcher.moe-nifty.com/memo/2005/11/bookey.html
        http://watcher.moe-nifty.com/memo/2005/12/bookey.html
        http://watcher.moe-nifty.com/memo/2006/02/bookey.html
        http://watcher.moe-nifty.com/memo/2006/03/bookey.html
        http://watcher.moe-nifty.com/memo/2006/04/bookey.html
        http://watcher.moe-nifty.com/memo/2006/05/bookey.html
        http://watcher.moe-nifty.com/memo/2006/06/bookey.html
        http://watcher.moe-nifty.com/memo/2006/06/bookey010.html
        http://watcher.moe-nifty.com/memo/2006/07/bookey.html
        http://watcher.moe-nifty.com/memo/2006/07/bookey012.html
        http://watcher.moe-nifty.com/memo/2006/07/bookey013.html
        http://watcher.moe-nifty.com/memo/2006/08/bookey013a.html
        http://watcher.moe-nifty.com/memo/2006/08/bookey.html
        http://watcher.moe-nifty.com/memo/2006/09/bookey.html
        http://watcher.moe-nifty.com/memo/2006/10/bookey.html
        http://watcher.moe-nifty.com/memo/2006/11/bookey.html
        http://watcher.moe-nifty.com/memo/2006/12/bookey.html
        http://watcher.moe-nifty.com/memo/2006/12/bookey022.html
        http://watcher.moe-nifty.com/memo/2006/12/bookey023.html
        http://watcher.moe-nifty.com/memo/2007/01/bookey.html
        http://watcher.moe-nifty.com/memo/2007/01/bookey025.html
        http://watcher.moe-nifty.com/memo/2007/02/bookey.html
        http://watcher.moe-nifty.com/memo/2007/02/bookey027.html
        http://watcher.moe-nifty.com/memo/2007/03/bookey.html
        http://watcher.moe-nifty.com/memo/2007/03/bookey029.html
        http://watcher.moe-nifty.com/memo/2007/03/bookey030.html
        http://watcher.moe-nifty.com/memo/2007/04/bookey031.html
        http://watcher.moe-nifty.com/memo/2007/04/bookey.html
        http://watcher.moe-nifty.com/memo/2007/07/bookey.html
        http://watcher.moe-nifty.com/memo/2007/07/bookey037.html
        http://watcher.moe-nifty.com/memo/2007/07/bookey038.html
        http://watcher.moe-nifty.com/memo/2007/07/bookey039.html
        http://watcher.moe-nifty.com/memo/2007/08/bookey.html
        http://watcher.moe-nifty.com/memo/2007/09/bookey.html
        http://watcher.moe-nifty.com/memo/2007/10/bookey.html
        http://watcher.moe-nifty.com/memo/2007/11/bookey.html
        http://watcher.moe-nifty.com/memo/2007/12/bookey.html
        http://watcher.moe-nifty.com/memo/2008/01/bookey.html
        http://watcher.moe-nifty.com/memo/2008/02/bookey.html
        http://watcher.moe-nifty.com/memo/2008/03/bookey.html
        http://watcher.moe-nifty.com/memo/2008/04/bookey.html
        http://watcher.moe-nifty.com/memo/2008/05/bookey.html
        http://watcher.moe-nifty.com/memo/2008/07/bookey.html
        http://watcher.moe-nifty.com/memo/2008/08/bookey.html
        http://watcher.moe-nifty.com/memo/2008/10/bookey.html
        http://watcher.moe-nifty.com/memo/2008/11/bookey.html
        http://watcher.moe-nifty.com/memo/2009/03/bookey.html
        http://watcher.moe-nifty.com/memo/2009/04/bookey.html
        http://d.hatena.ne.jp/tsupo/20051016
        http://d.hatena.ne.jp/tsupo/20051023
        http://d.hatena.ne.jp/tsupo/20051024
        http://d.hatena.ne.jp/tsupo/20051025
        http://d.hatena.ne.jp/tsupo/20060519
        http://d.hatena.ne.jp/tsupo/20060523
        http://d.hatena.ne.jp/tsupo/20060525
        http://d.hatena.ne.jp/tsupo/20060526
        http://d.hatena.ne.jp/tsupo/20060527
        http://d.hatena.ne.jp/tsupo/20060530
        http://d.hatena.ne.jp/tsupo/20060531
        http://d.hatena.ne.jp/tsupo/20060601
        http://d.hatena.ne.jp/tsupo/20060628
        http://d.hatena.ne.jp/tsupo/20060629
        http://d.hatena.ne.jp/tsupo/20060706
        http://d.hatena.ne.jp/tsupo/20060710
        http://d.hatena.ne.jp/tsupo/20060711
        http://d.hatena.ne.jp/tsupo/20060725
        http://d.hatena.ne.jp/tsupo/20060831
        http://d.hatena.ne.jp/tsupo/20060902
        http://d.hatena.ne.jp/tsupo/20060903
        http://b.hatena.ne.jp/entry/http://watcher.moe-nifty.com/memo/2005/10/bookey.html
        http://sites.google.com/site/tsujimura543/bookey
        http://github.com/tsupo/bookey/tree

  更新情報:
    Ver 0.63c 2009年 6月22日 「設定」ダイアログのタブの位置を上辺から右辺に変更
                             した
    Ver 0.63b 2009年 6月16日 (1) 登録しようとしている URL の長さが384バイト以上
                                 のとき、バッファオーバーランが発生する不具合を
                                 修正
                             (2) はてなブックマークプラスの人が「非公開」設定で
                                 ブックマークを登録しようとした場合、「この商品
                                 をコレクションに加える」指定時のみ、「非公開」
                                 で登録できるようにした (通常のブックマークは、
                                 API による登録のため、常に「公開」で登録されま
                                 す[現時点ではAPIによる非公開ブックマークの投稿
                                 を行なう方法がはてな側から提供されていません]が、
                                 「コレクション」の場合は、API を利用せず、はて
                                 なブックマーク投稿用の form 経由での投稿のため、
                                 「非公開」でも投稿可能になっています)
    Ver 0.63a 2009年 6月16日 (1) Twitter の OAuth 認証のアクセストークンを取得す
                                 るのに必要な PIN を入力するとき、PINが 0 で始ま
                                 ると「6桁の数字を入力してください」という警告が
                                 出続けて、先に進めない(キャンセルするしかない)
                                 不具合に対処
                             (2) 設定ダイアログの Twitter のタブのラジオボタンの
                                 動きがおかしかったのを修正 (連動してないはずのボ
                                 タン同士が連動していた)
                             (3) Twitter のユーザ名、パスワード未設定状態で、OAuth
                                 アクセストークン取得済み(OAuth 認証を使う設定)の
                                 とき、次回 bookey 起動時に「設定ファイルが壊れて
                                 いるようです」と表示される不具合を修正
    Ver 0.63  2009年 6月11日 Twitter の OAuth が 1.0 から 1.0a へ移行したのに伴い、
                             アクセストークン取得方法(OAuth経由でのアクセスを許可
                             する手続きの内容)が変わった。Twitter が(ブラウザ経由
                             で)返す6桁の数字(PIN)を入力するダイアログを新たに用
                             意した。
    Ver 0.62a 2009年 6月10日 Timelog へのブックマーク投稿時のレスポンスが変更され
                             たのに合わせて、投稿成功・失敗を判断する処理を変更し
                             た
    Ver 0.62  2009年 5月29日 同一アカウントで複数 tumblr を開設している場合、どの
                             tumbleblog を投稿先とするか、選択できるようにした
    Ver 0.61c 2009年 4月27日 「はてなブックマーク」のAPIの応答の形式が変更されたの
                             に伴う修正を実施 (2009年4月25日近辺に変更された模様)
    Ver 0.61b 2009年 4月 9日 Twitter の OAuth 認証でエラーが発生したときのレスポン
                             ス内容が変更されたのに伴う修正を実施
    Ver 0.61a 2009年 4月 7日 Twitter の OAuth 認証でエラーが発生したときの諸々の処
                             理を追加
    Ver 0.61  2009年 4月 1日 Twitter の OAuth 認証に対応
    Ver 0.60s 2009年 3月30日 (1) Yahoo! Japan の「形態素解析API」利用時のメモリ確
                                 保処理を修正(確保する領域が小さすぎてバッファオー
                                 バーランすることがある不具合に対処)
                             (2) xmlRPC.dllに組み込んでいる OpenSSL を 0.9.8j 版 
                                 から 0.9.8k 版に入れ替えた
    Ver 0.60r 2009年 3月23日 xmlRPC.dllに組み込んでいる OpenSSL を 0.9.8i 版 から
                             0.9.8j 版に入れ替えた
    Ver 0.60q 2009年 2月25日 「BlogPetブックマーク」の登録処理を修正 (初期化してい
                             ないメモリを参照している処理があった[が、メモリ参照エ
                             ラーが発生することなく、正常にブックマークの投稿ができ
                             ていた(ので、今まで気づいてなかった)]。当該処理自体、
                             すでに不要なので削除した)
    Ver 0.60p 2009年 2月25日 http://d.hatena.ne.jp/gyogyo6/20090225/bookmark を参考
                             に、ブックマークしようとしている記事の URL 末尾について
                             いる「ゴミ文字列」を削除する処理を書き直した(削除するパ
                             ターンを追加した)
    Ver 0.60o 2009年 2月24日 タグ候補を抽出するのに、Yahoo! Japan の「形態素解析API」
                             も利用するようにしてみた(「はてなブックマーク」のエント
                             リページから抽出したタグの候補が20件より少ない場合)
    Ver 0.60n 2009年 2月24日 「はてなブックマーク」のエントリページからタグ(候補)を
                             抽出する処理を、今のエントリページの仕様に合わせて改訂
    Ver 0.60m 2009年 1月30日 @nifty クリップの "setting" ページの内容変更に合わせて、
                             APIキー取得処理を書き直した
    Ver 0.60l 2009年 1月26日 「タグ候補を表示する」機能使用時、「はてなキーワード抽出
                             API」関連の処理で異常に時間がかかる不具合に対処。原因は、
                             「はてなキーワード抽出API」(hatena.setKeywordLink)の返す
                             レスポンスに予期しない文字列が大量に含まれているため。
                             [http://i.hatena.ne.jp/idea/23100 を参照]
    Ver 0.60k 2009年 1月19日 メインダイアログが最小化状態のときも、右クリックメニュー
                             から「ブックマーク管理ツール起動」と「設定」を実行できる
                             ようにした
    Ver 0.60j 2009年 1月 8日 (1) 「はてなブックマーク」の取得時、取得した URL が元記
                                 事への URL ではなくブックマーク自体の URL になってし
                                 まう不具合を修正 (RSS の中身が変更されたのに伴い発生
                                 するようになった不具合[変更時期は不明。0.60i版リリー
                                 ス時点ではまだ発生していなかった])
                             (2) 「Yahoo! ブックマーク」の取得時、コメントの中身が取
                                 得できなくなっていた不具合を修正   (「Yahoo! ブック
                                 マーク」の html 内容の変更に伴い、コメントが取得でき
                                 なくなっていた[変更時期は不明])
    Ver 0.60i 2008年12月16日 「はてなブックマーク」のタグ一覧取得機能を書き直すことに
                             より、再び、タグの置換、タグの削除を使えるようにした
                             (リニューアル以降、依然としてタグ取得用のAPIが使えないた
                              め、「はてなブックマーク」の自分のトップページのサイド
                              バーからタグ一覧を取得するようにした。なお、サイドバーに
                              タグ一覧を表示しない設定にしている場合は、いったんbookey
                              内部でタグ一覧を表示する設定に変更した後、トップページを
                              取得、タグ一覧を抽出後、タグ一覧の表示設定を元に戻してい
                              る。この変更の副作用として、取り扱い可能タグの最大数が
                              1000件から5000件に増えている)
    Ver 0.60h 2008年12月 4日 1470.net リニューアル版に「はてな認証」経由でログインする
                             処理を更新 (「はてな認証」手順が変更されていた[変更時期不
                             明])
    Ver 0.60g 2008年12月 3日 リニューアル後の「はてなブックマーク」の「AtomAPI EditURI
                             への URL クエリ」が機能していないため、エントリページのス
                             クレイピングで代用(必要な情報を取得)するようにしてみた(さ
                             らに、何らかの原因でスクレイピングがうまくいかない場合は、
                             livedoorクリップのエントリページから必要な情報を取得する
                             ようにした (「はてなブックマーク」の「AtomAPI EditURIへの
                             URL クエリ」は、すでに登録済みのエントリのコメント、タグ
                             を書き換えたい(上書き投稿したい)ときに、投稿済みエントリ
                             のコメント、タグの取得するのに利用している。取得したコメ
                             ント、タグを「ブックマーク登録ダイアログ」にて修正後、上
                             書き登録することができるようになっている)
    Ver 0.60f 2008年12月 2日 TypePad Connect 経由で MM/Memo にログインしようとしたとき
                             に、MM/Memo側で何らかのトラブルが発生していて、再度ログイ
                             ンし直すよう求められる状況が無限に続く、といった事態に陥る
                             ことが判明。ログインし直し要求が6回続いたところで「ログイ
                             ン失敗」と判定することで、いつまでも経ってもログイン処理が
                             終わらない状態になるのを防止するようにした
    Ver 0.60e 2008年12月 2日 (1) バッファオーバーフローが発生する可能性のある箇所を修正
                             (2) nullポインタ参照が発生する可能性のある箇所を修正
                             (3) フォーマットストリング関連の問題のある箇所を修正
                             (4) (将来も使う予定のない)余分な処理やメモリ領域を削除
    Ver 0.60d 2008年12月 1日 URL に & が含まれると、「はてなブックマーク」への「登録」が
                             失敗することが判明、対処した(「はてなブックマーク」リニュー
                             アル後、発生するようになった模様)
    Ver 0.60c 2008年11月28日 (1) 「はてなブックマーク」の「削除」API の実行に失敗した場
                                 合は、Webスクレイピングによる「削除」を試みるようにし
                                 てみた
                             (2) 「はてなブックマーク」の「取得」時の情報源を atomfeed
                                 から rss に変更してみた (この結果、タグ情報が取得でき
                                 るようになる一方、エントリIDが取得できなくなる)
                             (3) エントリIDが取得できない状況では、「はてなブックマー
                                 ク」の「削除」は、常にWebスクレイピングによる「削除」
                                 の方を実行するようにした
    Ver 0.60b 2008年11月28日 (1) リニューアル後の「はてなブックマーク」で「コレクション
                                 への追加」ができなくなってしまっていたのを、再びできる
                                 ように調整した
                             (2) 「はてなブックマーク」の「取得」、「削除」、「タグの一
                                 括置換」、「タグの一括削除」関連処理を調整した(が、タグ
                                 の一覧の取得ができないため、現状のままでは、タグの一括
                                 置換・一括削除処理までたどりつけない。1日も早く、はてな
                                 ブックマークの API が正常に機能するようになって欲しいと
                                 ころ)。
                                 なお、「取得」処理でタグ情報が取得できていないのは、API
                                 の返す情報にタグ情報が含まれなくなってしまっているため
    Ver 0.60a 2008年11月27日 版数表示ダイアログで、OpenSSL と iconv の版数も表示するよう
                             にした
    Ver 0.60  2008年11月26日 xmlRPC.dllに組み込んでいる OpenSSL を 0.9.8g 版 から 0.9.8i
                             版に入れ替えた
    Ver 0.59i 2008年11月25日 (1) 「はてなブックマーク」がメインテナンス中のときに、
                                 charset=Shift_JIS なページをブックマークしようとすると、
                                 ブックマーク登録ダイアログに表示される title が文字化け
                                 する不具合に対処
                             (2) Flog の「取得」処理を更新
                             (3) JoltMark の「登録」処理を更新
                             (4) MM/memo、1470.net の TypeKey 認証回りの処理を、TypePad
                                 Connect 対応するよう書き換えた
                             (5) 1470.net の「取得」処理を更新
    Ver 0.59h 2008年11月18日 (1) Yahoo! および Yahoo! Japan を除いて、login の必要なサー
                                 ビスはすべて cookie をキャッシュするようにした(まだ、
                                 キャッシュを導入していなかったサービスがいくつか残って
                                 いた)
                             (2) xmlRPC.dll 内のバッファオーバーフロー脆弱性対策を強化
                             (3) xmlRPC.dll 内のスレッドセーフ未対応だった処理をスレッ
                                 ドセーフにした
    Ver 0.59g 2008年11月17日 Twitter へのブックマーク投稿時、対象 URL に ? または # が
                             含まれる場合、かつ TinyURL を適用する必要がある場合に、URL
                             を (null) で投稿してしまう不具合を修正 (TinyURL のレスポン
                             スの形式が変更されたのが原因。いつ変更されたのかは不明)
    Ver 0.59f 2008年11月13日 (1) 0.59d版で実施した対策に関して不具合を発見、修正を実施
                             (2) Buzzurl の設定画面(日本語モード時)を調整し直した
                             (3) Twitter の設定画面(日本語モード時、英語モード時とも)の
                                 文言の一部を修正
                             (4) @niftyクリップの設定画面の「Powered by @nifty クリップ」
                                 部分に下線を表示するように修正
    Ver 0.59e 2008年11月11日 @niftyクリップの取得と削除にも APIキー(が設定済みであれば)を
                             使うようにしてみた
    Ver 0.59d 2008年11月10日 「APIキー」の設定内容が破壊される(decode後のAPIキーが元のAPI
                             キーの先頭何文字かになってしまう(短くなってしまう))現象に対
                             する対策を実施 [Ver 0.07 の (5) と同じ対策]
    Ver 0.59c 2008年11月 5日 (1) @niftyクリップの設定ダイアログの「APIキー取得」ボタンを
                                 押したときに実行される処理を修正
                             (2) @niftyクリップのAPIキーを取得、設定済みの場合は、ブック
                                 マーク(クリップ)の登録時にAPIキーを使うようにしてみた
    Ver 0.59b 2008年11月 4日 (1) @niftyクリップのログイン処理を修正 (2008年11月3日、もし
                                 くはそれ以前にログイン回りの仕様が変更された模様)
                             (2) @niftyクリップの取得ができなくなってしまっていたのを、取
                                 得できるように修正 (AutoPagerize 対応時に html の構造が
                                 変更されたのが原因。変更時期は不明)
                             (3) ブックマーク登録ダイアログに @niftyクリップでの登録者数
                                 も表示するようにした (登録者数を表示する設定にしている場
                                 合)
                             (4) @niftyクリップの設定ダイアログに「APIキー取得」ボタンを
                                 追加。bookey では、いまのところ APIキーは使用していない
                                 が、将来の版で使用するように変更する予定
    Ver 0.59a 2008年10月22日 (1) メインダイアログのタイトルバー右クリック時のメニューにも
                                 4つのメニューと「バージョン情報」の計5つのメニューを追加
                             (2) 「バージョン情報」を「bookey について」に名称変更
                             (3) メインダイアログから各種ダイアログを起動している間、「閉
                                 じる」ボタンを disable にするようにした
    Ver 0.59  2008年10月21日 (1) メインダイアログの「ヘルプメニュー」に「サポート (公式ブ
                                 ログ)」、「サポート (Google Sites)」、「コミュニティ (は
                                 てなブックマーク)」、「コミュニティ (wakoopa)」の4つのメ
                                 ニューを追加
                             (2) 「ブックマーク管理ツール」ダイアログ表示時のツールバーを
                                 右クリックしたときに表示されるメニューにも上記と同様の4つ
                                 のメニューを追加
    Ver 0.58b 2008年10月21日 リダイレクト対策 URL に sum.com と amazon.com のメールマガジ
                             ン掲載用リダイレクタを追加
    Ver 0.58a 2008年10月20日 newsing のログイン処理を修正 (ログインページからトップページ
                             へ遷移するまでの間に挿入される中間ページの内容が変更されたの
                             に伴う修正。変更された時期は2008年10月15日ごろ?)
    Ver 0.58  2008年 9月 2日 xmlRPC.dll の機能を整理、軽量化してみた。bookey 本体は変更し
                             ていない
    Ver 0.57d 2008年 8月18日 Diigo への登録失敗時、Diigo からの応答内容によっては bookey
                             が異常終了してしまう不具合に対処
    Ver 0.57c 2008年 8月12日 (1) FC2BOOKMARK の登録に成功していても「失敗しました」ダイ
                                 アログが表示されてしまう件に関して、登録成功・失敗判定
                                 処理を修正(追加)することで対応した
                             (2) Diigo の登録失敗時にサーバからエラー内容を示すメッセー
                                 ジが返ってきている場合は、ダイアログで表示するようにし
                                 てみた
    Ver 0.57b 2008年 8月 3日 (1) 2008年7月31日(日本時間2008年8月1日)の del.icio.us →
                                 delicious.com への移行(デザイン変更)に対応するための変
                                 更を実施 (API は従来のものがそのまま使用できるので、変
                                 更せず[いずれは、URL を変更しないといけなくなるかもしれ
                                 ない]。API不調時の代替処理としてスクレイピングが必要な
                                 処理のみ修正)
                             (2) clcoo.exe, d2hb.exe を同梱するのを終了
    Ver 0.57a 2008年 7月28日 (1) livedoorクリップの「削除」失敗時、del.icio.us互換APIによ
                                 る「削除」を試みる機能を追加 (事前にAPIキーの設定が必要)
                             (2) はてなブックマークのエントリページの仕様変更により、再投
                                 稿時に前もって自分の投稿済みコメントを取得する処理が期待
                                 通りの動きをしなくなってしまった件に対処した (2008年7月
                                 中旬から発生していた現象)
    Ver 0.57  2008年 7月26日 Diigo の登録、取得、同期に対応した (削除にも対応しようとしま
                             したが、今のところ、うまく動いていません)
    Ver 0.56  2008年 7月25日 (1) del.icio.us と faves.com の private saving に対応
                                 (登録、取得、削除)
                             (2) del.icio.us の hash key の長さが32バイト固定でなくなった
                                 ことが判明。最大64バイトまで対応できるように修正した
                             (3) ブックマークを1個づつ削除するダイアログの挙動を修正(すで
                                 に前方のブックマークを削除した結果、実際には戻ることが可
                                 能なブックマークが存在しなくなった場合でも「1個前に戻る」
                                 ボタンが押せてしまう不具合を修正)
    Ver 0.55d 2008年 6月12日 rss.yomiuri.co.jp/click.phdo のリダイレクタにも対応
    Ver 0.55c 2008年 5月21日 ブックマーク同期時、「一気に登録する」を選択すると、URL に
                             & が含まれる場合、&amp; (正確には &amp; が &amp;amp;)に変換
                             されて登録されてしまう不具合を修正
    Ver 0.55b 2008年 5月20日 ブックマーク登録時のタグ候補抽出処理実行時にスタックオーバー
                             フローもしくはバッファオーバーランが発生することがある不具
                             合に関する対策を実施 (例えば、はてなダイアリーキーワード自
                             動リンクAPIが停止中のときに
                              http://japan.cnet.com/news/biz/story/0,2000056020,20373566,00.htm
                             をブックマークしようとすると発生する)
    Ver 0.55a 2008年 5月19日 (1) ブックマーク同期処理(URL に &amp; が含まれる場合の扱い)
                                 を修正
                             (2) 同期対象の一方が「ローカルOPML」の場合、ローカルOPMLの
                                 取得を行なわずに同期を実行しようとしてしまう不具合を修
                                 正(日本語モードの場合のみ)
                             (3) ダイアログで「BlogPetブックマーク」の削除を選択しても
                                 削除処理が実行されない不具合を修正 (日本語モード、英語
                                 モードとも。0.53e版以降で発生する不具合)
    Ver 0.55  2008年 5月16日 (1) del.icio.us から取得したブックマークの URL に &amp; か
                                 &amp;amp; のどちらかが含まれる場合の処理を修正
                             (2) del.icio.us のブックマーク取得 API が 503 エラーを返し
                                 てきたときは、html ページのスクレイピングによるブック
                                 マーク取得を試みるようにした
                             (3) ブックマーク同期処理時の進行中ダイアログの文言(および
                                 ログ記録モードが有効な場合のログに記録する文言)の間違
                                 いを修正 (フォーマット指定文字列 %s がそのまま出力さ
                                 れていた)
    Ver 0.54g 2008年 5月16日 (1) ブックマーク取得処理失敗時(1件も取得できなかったとき)
                                 に、参考用として http のステータスコードを表示するよう
                                 にした (4xx 系、5xx 系 のエラーが発生している場合のみ)
                             (2) はてなブックマークとdel.icio.us間の同期を行なうとき、
                                 del.icio.us側のブックマーク情報を格納しているメモリ領
                                 域でメモリ破壊が起きる可能性があることが判明、対策を施
                                 した
                             (3) c2.lenovo-news.com/g.php のリダイレクタにも対応
    Ver 0.54f 2008年 5月14日 (1) symantecenterprise.rsys3.net と www.oracle.co.jp/mp の
                                 リダイレクタにも対応
                             (2) 「はてなブックマーク」に関してのみ、 bookey の「タイト
                                 ルの設定」のデフォルト値を「自分が指定するものを使用す
                                 る」ではなく「すでに登録済みのものを使用する」にするよ
                                 うに仕様変更
    Ver 0.54e 2008年 5月13日 feeds.japan.cnet.com のリダイレクタに対応
    Ver 0.54d 2008年 5月 7日 (1) JoltMark, FC2BOOKMARK, Flog の各設定画面で「同時ブック
                                 マーク対象」の設定を変更しても、反映されない不具合を修
                                 正 (この不具合は 0.35c版以降で発生する)
                             (2) ローカルOPML関連の設定を変更しても、反映されない不具合
                                 を修正 (この不具合は 0.52版以降で発生する)
    Ver 0.54c 2008年 4月15日 (1) ブックマーク登録ダイアログに表示するブックマーク対象Web
                                 ページのタイトルに &lt;, &gt;, &quot; が含まれる場合は、
                                 各々 <, >, ' を表示するように変更 (このまま登録すると、
                                 tumblr 等、&amp;lt; のように解釈されてしまうサービスが
                                 存在するため)
                             (2) ブックマーク削除/同期時の個別ブックマーク表示ダイアログ
                                 に表示するタイトルに &lt;, &gt;, &quot; が含まれる場合は、
                                 各々 <, >, ' を表示するように修正
    Ver 0.54b 2008年 4月 2日 @nifty クリップのログイン処理を更新 (2008年4月1日に login
                             直後に表示される html の内容が変更された影響で、ログイン
                             成功・失敗の判定処理がうまく動かなくなった)
    Ver 0.54a 2008年 3月17日 (1) POOKMARK Airline の登録処理を更新 (2008年3月15日に登
                                 録に必要な引数が追加された)
                             (2) del.icio.us の「総ブックマーク件数」取得処理を修正
                                 ユーザ名の末尾に数字が含まれる場合でも、正しいブック
                                 マーク件数を取得できるようにした
                             (3) @nifty クリップのログイン処理を更新 (2008年3月17日に
                                 login 用の form の仕様が変更された模様)
                             (4) @nifty クリップのタグの(取得、)置換、削除の各処理を
                                 2008年3月11日リニューアル版に合わせて修正した
    Ver 0.54  2008年 3月12日 「ニフティクリップ」がリニューアルして「@nifty クリップ」
                             になったのに対応して、ニフティクリップの「登録」、「取得」、
                             「削除」処理を修正した (タグの置換機能は未修正。次の版で
                             対応予定)
    Ver 0.53j 2008年 3月10日 livedoorクリップのログイン後に表示される画面(というか、ロ
                             グアウトの仕方)の変更(2008年3月7日実施)に伴い、実際にlogin
                             できたかどうか判定する処理がうまく動かなくなってしまったた
                             め、「livedoorクリップへのログイン処理」を修正
    Ver 0.53i 2008年 2月27日 ディスプレイの縦方向のサイズが800px以下の場合は、「設定ダ
                             イアログ」の縦方向を小さくしたものを表示するようにした
                             (720px [0.53f版] → 800px [0.53i版] に条件を変更した)
    Ver 0.53h 2008年 2月25日 Blue Dot (Faves.com) の「取得」処理を修正
    Ver 0.53g 2008年 2月23日 (1) livedoorクリップの「取得」時、サーバから空、もしくは
                                 ブックマーク情報の入っていない応答が返ってきた場合の
                                 リトライ処理を追加した (最大5回、2秒間隔で再試行)
                             (2) livedoorクリップの「取得」処理で、各応答の最後のブッ
                                 クマークがプライベートであるか、R18フラグが立っている
                                 かの少なくともどちらかの場合(同時に両方の状態になって
                                 いる場合を含む)、そこで処理を終了してしまい、それ以降
                                 のブックマークを取得しに行かない不具合を修正
    Ver 0.53f 2008年 2月20日 ディスプレイの縦方向のサイズが720px以下の場合は、「設定ダ
                             イアログ」の縦方向を小さくしたものを表示するようにした
    Ver 0.53e 2008年 2月19日 (1) 「BlogPet 気になる記事」から「BlogPetブックマーク」に
                                 名称変更
                             (2) 「BlogPetブックマーク」からのブックマーク取得時、
                                (a) title 属性の先頭および末尾にホワイトスペースが存在
                                    する場合はホワイトスペースを削除するようにした
                                (b) title 属性中に改行が含まれる場合は、改行を削除する
                                    ようにした
                                (c) コメントが空の場合、notes 属性が "(コメントがあり
                                    ません)" になってしまっていたのを、空のままにする
                                    ようにした (BlogPet 側で何らかの仕様変更があった?)
                             (3) tumblr の API 改訂に伴い、tumblr への link 登録時、
                                 tags 引数を指定するようにした(タグが指定されている場合)
    Ver 0.53d 2008年 2月14日 0.53c版で導入した対策を comment 部分にも適用するようにした
    Ver 0.53c 2008年 2月14日 tumblr への link 投稿時、&laquo; および &raquo; 相当文字が
                             tumblr側で自動的に &Lt; および &Gt; に各々変換されてしまう
                             件の対策として、bookey 側で事前に3バイト表現から2バイト表
                             現に変換しておくことで対処した
    Ver 0.53b 2008年 2月 8日 「はてなブックマーク」の「コレクション」に登録できなくなっ
                             てしまっていた不具合に対処 (「コレクション」へ登録するAPI
                             は存在しないので、スクレイピングにより実現。ログイン時のパ
                             ラメータが変更された(変更時期は不明)ため、ログインに失敗し、
                             結果的に登録できなくなっていた)
    Ver 0.53a 2008年 1月25日 「BlogPetブックマーク」のユーザ名、パスワードにマルチバイ
                             ト文字を使っている場合でも、「登録」、「取得」、「削除」、
                             「同期」が使えるようにした
    Ver 0.53  2008年 1月24日 (1) livedoorクリップの「取得」時、18禁フラグの立っているク
                                 リップの取得に失敗する不具合を修正
                             (2) livedoorクリップの「取得」時、取得に失敗したクリップが
                                 1件でも存在すると、最終ページを無限に取得し続ける不具
                                 合を修正
                             (3) ブックマークの取得時、全件取得に失敗した場合でも、1割
                                 以上のブックマーク情報の取得に成功しているときは、ブッ
                                 クマーク情報を破棄せずに、保持するようにした(取得後、
                                 ファイルに保存したり、編集したりできるようにした)
    Ver 0.52i 2007年12月19日 asahi.com 以外で、最近、RSS中に含まれる記事 URL が変わった
                             もの(のうち、当方が気が付いたもの)についても対応を行なった
    Ver 0.52h 2007年12月17日 asahi.com の RSS 中に含まれる記事 URL が pheedo 経由のもの
                             に変更されたのに伴う修正を実施 (いつ変更されたのかは不明)
    Ver 0.52g 2007年12月 6日 xmlRPC.dll を更新(バイナリファイルの送信に対応)。bookey で
                             は未使用の機能のため、0.52g版は0.52f版と機能的な違いはない
    Ver 0.52f 2007年11月30日 (1) bookey.exe.manifest を同梱するようにした
                             (2) xmlRPC.dll から不要になった処理を削除
    Ver 0.52e 2007年11月21日 xmlRPC.dll に込みこんでいる OpenSSL を 0.9.8g 版に入れ替えた
    Ver 0.52d 2007年11月16日 BlogPetブックマーク登録時、登録しようとしているブックマー
                             クのタイトルが空文字列になってしまい、登録に失敗する現象に
                             対処するコードを追加(2007年11月13日未明、gooブログの記事を
                             登録しようとしたときに頻発。問題が発生した記事に関して、
                             2007年11月13日午後以降は問題なく登録できるため、サーバ側で
                             何らかの対処が行なわれた可能性があるが、bookey 側での対策
                             コードも残しておく)
    Ver 0.52c 2007年11月12日 (1) はてなブックマーク、del.icio.us、Flog への登録時、ブッ
                                 クマークのコメントの文字コード変換結果がおかしい場合に
                                 文字化けが発生する、もしくは bookey 自体が落ちる不具合
                                 に対処 (Shift_JIS なのか EUC-JP なのか、どちらとも自動
                                 判定しにくいときに発生する問題)
                             (2) BlogPetブックマーク登録時、登録しようとしているブック
                                 マークのタイトルが長すぎる(全角50文字より長い)場合は、
                                 あふれた部分を切り捨ててから登録するようにした
                             (3) tumblr への登録失敗時、エラーメッセージを表示可能な場
                                 合(エラー発生原因がサーバ側から通知された場合)は表示
                                 するようにした
    Ver 0.52b 2007年11月 9日 BlogPetブックマーク登録時に、エラーが発生した場合、どうい
                             うエラーが起きているのかの情報が得られたときは、その情報
                             (エラー発生原因)を表示するようにした
    Ver 0.52a 2007年11月 7日 2007年11月6日に実施されたlivedoorクリップの html ページの
                             フォーマットの変更にあわせて、livedoorクリップのログイン成
                             功/失敗判定処理を改定
    Ver 0.52  2007年11月 5日 (1) Buzzurlとnewsing へのアクセスを共に Yahoo! Japan の ID
                                 で行なう場合の対策を実施 (ほとんど効果なし。引き続き、
                                 対策を検討する)
                             (2) tumblr への link 形式による投稿に対応
    Ver 0.51  2007年10月13日 Yahoo! Japan の ID による newsing への投稿に対応 (Buzzurlと
                             newsing へのアクセスを共に Yahoo! Japan の ID で行なう場合、
                             newsing へのログインに失敗することがあることがわかっている。
                             現在、対策を検討中)
    Ver 0.50  2007年10月11日 (1) Yahoo! Japan の ID による Buzzurl へのログイン処理関連
                                 のリカバリ方法を修正
                             (2) digg の CAPTCHA画像まわりの仕様変更に対応(ディレクトリ
                                 構成が変わった、画像取得に cookie が必要になった、等)
                             (3) digg のカテゴリ名に空白文字がある場合にカテゴリIDの取
                                 得に失敗する不具合を修正
                             (4) newsing のログイン成功・失敗判定条件を修正
    Ver 0.49  2007年10月10日 (1) Yahoo! Japan の ID による Buzzurl へのログイン失敗時の
                                 リカバリ処理を修正
                             (2) Yahoo! Japan の ID による Buzzurl へのブックマーク投稿
                                 時、キーワード(タグ)が設定されない不具合を修正
                             (3) Yahoo! Japan の ID による Buzzurl のブックマークの削除
                                 もしくは同期の実行時、ユーザ名確認ダイアログで、Yahoo!
                                 Japan の ID/パスワードではなく、Buzzurl自体のユーザ名
                                 (メールアドレス)/パスワードの方を表示してしまう不具合
                                 を修正(ただし、パスワードは **** のようにマスク状態で
                                 表示される)
    Ver 0.48  2007年10月 5日 Yahoo! Japan の ID による Buzzurl へのログインを連続して行
                             なうと、ログインに失敗することがあることが判明。対策を実施
    Ver 0.47  2007年10月 5日 Yahoo! Japan の ID による Buzzurl のブックマーク登録、取得、
                             削除、同期に対応した
    Ver 0.46  2007年 9月26日 FC2ブックマークの仕様変更(2007年9月20日実施?)に対応
    Ver 0.45  2007年 9月10日 Buzzurl からブックマークを取得する処理で、コメントとタグが
                             取得できない不具合に対処 (Buzzurl の html フォーマットが微
                             妙に変更されたのが原因)
    Ver 0.44  2007年 9月 7日 (1) 「進捗状況表示ダイアログ」の文言変更のタイミングで、ロ
                                 グに、進捗状況を出力するようにした(ログ出力機能作動時)
                             (2) 各サーバに送る User-Agent: を bookey で統一した
                             (3) はてなブックマークの登録、編集時にコメント、タグの両方
                                 とも空の場合は API を実行せずに中止していたのを、APIを
                                 実行するようにした
    Ver 0.43  2007年 9月 5日 bookey がうまく動かない場合に調査をしやすくするため、ログを
                             ファイルに出力する機能を実装。設定ファイル(bookey.inf)に
                               verbose: TRUE
                             の1行を追加することで、この機能がアクティブになる(この行を
                             追加しても、その後、削除すれば、ログ出力機能が動作しない状
                             態に戻る)。bookey の動作がおかしい場合は、このログを取得し、
                             zip か lzh 形式で圧縮してメールで送ってもらえば、調査します。
    Ver 0.42  2007年 8月28日 (1) digg のデザイン変更に対応 (カテゴリID取得処理を修正)
                             (2) ブックマーク登録・編集ダイアログを修正し、同時登録対象に
                                 なっているブックマークのアイコンを「くぼみ」表示するよう
                                 にした
                             (3) digg 専用投稿ダイアログのコメント入力欄のスタイルを修正
                                 (垂直スクロールにするべきところを水平スクロールにしてい
                                 た)
    Ver 0.41  2007年 8月28日 「はてなスター」に対応。ブックマーク登録・編集ダイアログから
                             ☆をつける機能を実装した。
    Ver 0.40  2007年 8月24日 (1) FC2BOOKMARKのページデザイン変更(2007年8月23日実施)に伴い、
                                 FC2BOOKMARKへの登録処理、FC2BOOKMARKからの取得処理を修正
                                 した
                             (2) Buzzurl のトップページのデザイン変更(8月10日ごろ実施)に
                                 伴い、ユーザ名取得処理を修正した。この修正により、Buzzurl
                                 からのブックマーク取得処理と、ブックマーク削除処理がうま
                                 く動かなくなってしまっていた不具合が解消された(ブックマー
                                 ク登録処理はAPIを利用しているため、ページデザインの変更
                                 の影響はない[ので、今回は何もいじっていない])
    Ver 0.39  2007年 7月27日 同時投稿の対象にしていないサービスを「一時的に on にする」機
                             能を実装 (ブックマーク投稿ダイアログの右クリックメニューを改
                             良) した
    Ver 0.38  2007年 7月13日 (1) 環境によっては、digg への登録(投稿)の「一時的に off にす
                                 る」/「on に戻す」の切り替えができない不具合に対処
                             (2) 環境によっては、digg への登録処理が全く呼び出されない不
                                 具合に対処
                             (3) BlogPet のリニューアルに合わせて「BlogPet 気になる記事」
                                 の登録、取得、削除処理を書き直した
    Ver 0.37  2007年 7月10日 (1) digg への登録(投稿)に対応した
                             (2) Twitter への投稿時、source 指定つきで投稿するようにした
                             (3) del.icio.us posts/all 形式のファイルからのインポート時、
                                 微妙に del.icio.us の形式と違っていてもインポートできる
                                 ようにしてみた( “/>”の直前に white space がない場合で
                                 もインポートできるようにした)
    Ver 0.36a 2007年 7月 2日 (1) 「タグ候補を表示」するようにしていると、1470.net のタグ
                                 候補抽出API呼び出し直後に落ちるようになってしまった不具
                                 合に対処 (0.36版で発生する不具合)
                             (2) MM/Memo の URL 変更に対応しきれていなかったところを発見、
                                 修正を実施 (再び、MM/Memo への「登録」ができるようになっ
                                 た)
                             (3) 1470.net リニューアル版の「登録」処理の成功・失敗の判断
                                 方法を修正(1470.net のデザイン変更の影響で正しく判断でき
                                 なくなっていた)
                             (4) 1470.net リニューアル版の「取得」処理の成功・失敗判定条
                                 件を修正 (「今日」登録したブックマークが0件の場合に即座
                                 に取得失敗と判断してしまう不具合に対処)
                             (5) Twitter への投稿時に記事題名が文字化けすることがある不具
                                 合に対処(投稿内容を140バイト以内に切り詰める処理を実行す
                                 る直前と直後に不具合があった)
    Ver 0.36  2007年 6月27日 (1) (proxy サーバ経由など) TypeKey 認証に失敗することがある
                                 現象に対処
                             (2) MM/Memo の URL 変更に対応
                             (3) 1470.net リニューアル版のメモ取得API が 404 エラーを返す
                                 場合は、即座にブックマーク取得処理を打切るようにした
    Ver 0.35d 2007年 6月26日 はてなダイアリーキーワードAPI が運用停止中のときに、タグ候補
                             抽出処理で落ちることがある不具合に対処
    Ver 0.35c 2007年 6月 8日  (1) はてなブックマークのエントリページのデザイン変更に合わ
                                  せて、タグ候補取得処理を変更
                              (2) FC2BOOKMARK への登録時に proxy error が返ってきた場合は、
                                  「もう一度、試しますか?」ダイアログを出すようにしてみた
                                  (ここ最近、「何らかのエラーが発生しました」になる現象が
                                   頻発しているため、何が起きているのか調査していたところ
                                   proxy error が返ってきていることが判明。実際には登録に
                                   成功していることもあるし、再度登録を試みれば成功するこ
                                   ともある)
                              (3) Blue Dot への登録時にサーバが空の応答を送ってきた場合は、
                                  もう一度だけ(自動的に)登録を試みるようにした (このリトラ
                                  イ処理でほぼリカバリできている)
                              (4) ユーザ名、パスワードの指定が必要なプロキシサーバを使う
                                  場合に、設定ファイルに保存したユーザ名、パスワードを使
                                  わずに、ユーザ名、パスワードとも未設定状態のまま、http
                                  リクエストを送信してしまうことがある不具合に対処
    Ver 0.35b 2007年 6月 7日  ローカルOPMLに関する設定が設定ファイルに保存されなくなって
                              しまっていた不具合(0.35版以降で発生する不具合)を修正
    Ver 0.35a 2007年 5月26日  (1) ユーザ名とパスワードの指定が必要な proxy サーバ経由で
                                  Twitter にアクセスする場合、ユーザ名とパスワードを指定し
                                  ているにも関わらず、proxy サーバから 407 エラーが返って
                                  くることがある現象に対 する対策(BCSIクッキーの併用、リ
                                  トライ処理の実行)を強化
                              (2) 時間のかかる処理実行中の画面の再描画タイミングを変更
                                  (500ミリ秒ごとに再描画 → 400ミリ秒ごとに再描画に変更)
    Ver 0.35  2007年 5月23日  (1) ユーザ名とパスワードの指定が必要な proxy サーバ経由で
                                  BASIC認証の必要なWebサーバへアクセスした時に、proxy サー
                                  バが 407 エラーを返すことがある現象に対処
                              (2) Timelog への投稿(報告)に対応した
    Ver 0.34c 2007年 5月22日  (1) ユーザ名とパスワードの指定が必要な proxy サーバ経由での
                                  Web アクセスに対応 (動作確認完了)
                              (2) http 通信時に独自のルート証明書の使用を要求する proxy 
                                  サーバ経由での Web アクセスに対応
                              (3) 上記 (1)、(2) の対応作業時に判明した、既存の http/https
                                  通信回りの処理の修正 (安定化)
                              (4) 設定ダイアログのデザインを微調整
    Ver 0.34b 2007年 5月11日  (1) Twitter への投稿時、記事の題名が長すぎるときに短くする
                                  処理の不具合で題名の末尾付近で文字化けが発生することが
                                  ある現象に対処
                              (2) Twitter への投稿時の User-Agent に設定する版数を bookey
                                  の版数に合わせて変更するようにした(今までは常に 0.31 固
                                  定だった)
    Ver 0.34a 2007年 4月25日  (1) 1470.net のタグ候補抽出APIで(今までに観測したことのある
                                  のとは別の)異常が発生している場合の対処を追加
                              (2) vector.co.jp の RSS フィード中に含まれるリダイレクタ、
                                  マイクロソフトのメールマガジンに含まれるリダイレクタ、
                                  および pheedo.com のリダイレクタに対応
    Ver 0.34  2007年 4月20日  (1) Yahoo! ブックマーク および Yahoo! Bookmarks の取得(イン
                                  ポート)、エクスポート、同期、削除に対応した
                              (2) OPMLファイル出力処理で、コメント部分に生の & が存在する
                                  場合は &amp; に置換してから出力するように修正した
    Ver 0.33  2007年 4月18日  Yahoo! Bookmarks (yahoo.co.jp ではなく yahoo.com の方)の「登
                              録」に対応
    Ver 0.32  2007年 4月16日  (1) ドリコムRSS(ドリコムアカウント)のログアウト方法が変更さ
                                  れたのに伴う修正を実施
                              (2) del.icio.us の posts/all 形式の XML ファイルのインポート、
                                  エクスポートに対応
                              (3) Yahoo! ブックマークの「登録」に対応
                              (4) Yahoo! ブックマークのリダイレクタに対応 (Yahoo! ブックマー
                                  クを閲覧中に表示されている URL を bookey に対してドラッ
                                  グ&ドロップでもってきた場合でも、本来の URL で登録できる
                                  ようにした)
    Ver 0.31b 2007年 4月12日  (1) 2007年4月12日に実施されたドリコムRSSのリニューアルに対応
                              (2) Twitter への報告登録時に使用する tinyurl の短縮URL生成処
                                  理を修正し、? や # が含まれる URL も正しく tinyurl でき
                                  るようにした
    Ver 0.31a 2007年 4月11日  httpレスポンスのヘッダの Content-type: が appliction/xml,
                              application/xhtml+xml 等、text/ 以外で始まる場合は無条件に
                              バイナリファイルとして処理するようにしていた(0.30a版以降)関
                              係で、xml ファイルとして正しく処理できない場合がある不具合
                              を修正 [xmlRPC.dll を修正] (bookey ではこの不具合が影響する
                              使い方をしていないので、0.31版のままでも特に問題はないが、
                              念のために 0.31a 版を用意した)
    Ver 0.31  2007年 4月11日  (Twitter の followers 向けにお試し公開)
                              (1) bookey 起動時に「プロキシサーバに関する設定を確認する
                                  ダイアログ」を出すのはやめ、「プロキシ設定ボタン」押下
                                  時のみ、設定変更が可能にしてみた
                              (2) Twitter に報告するときの User-Agent を Twitter の規約
                                  にしたがって設定するようにした
                              (3) Twitter への報告登録時に使用する tinyurl の短縮URL生成
                                  結果にゴミが混じることがある現象に対処
    Ver 0.30b 2007年 4月10日  (Twitter の followers 向けにお試し公開)
                              (1) 「プロキシサーバに関する設定を確認するダイアログ」が出
                                  続ける件に関して、さらに対策を実施
                              (2) 「ローカルOPML」の設定画面でOPMLファイル名を設定しても
                                  設定内容が反映されずに消えてしまうことがある不具合に対
                                  処
                              (3) 登録しようとしているブックマークを Twitter に報告する
                                  機能を追加
    Ver 0.30a 2007年 4月 9日  (未公開)
                              (1) プロキシサーバに関する設定を確認するダイアログに対して、
                                  「プロキシサーバを利用しない」旨の返答をした場合、この
                                  ダイアログが出続けて先に進めないことがある不具合に対処
                              (2) 短縮URL生成サービスのうち、tinyurl.com と rurl.org に
                                  よる短縮URLをブックマークしようとした場合、短縮URLでは
                                  なく、その短縮URLに対応する実体の方のURLをブックマーク
                                  するようにした
    Ver 0.30  2007年 3月30日  FC2BOOKMARK の登録、取得、削除、同期に対応した
    Ver 0.29d 2007年 3月28日  (1) Buzzurl へのブックマーク登録時、タグにマルチバイト文字
                                  が含まれる場合に、最初のタグしか登録されない不具合に対
                                  処 (0.29b で投稿APIに対応したときにバグを作りこんでし
                                  まっていた)
                              (2) ブックマーク登録処理中は、「プロキシサーバ情報設定」ボ
                                  タンを押せないようにした
    Ver 0.29c 2007年 3月27日  (1) ローカルOPMLへのブックマーク登録時、バッファオーバーラ
                                  ンが発生し、タイムスタンプ情報が破壊されたり、ファイル
                                  が消えてしまったりすることがある不具合に対処
                              (2) ブックマーク登録待ち行列に複数のURLが入っているときに、
                                  デッドロックが発生することがある不具合に対処
                              (3) 「プロキシサーバ情報設定」ボタンを追加
    Ver 0.29b 2007年 3月20日  (1) proxy情報の設定のみいったん初期状態に戻すとき、初期設定
                                  ファイルへの反映が必要な場合は、反映するようにした
                              (2) Buzzurl への投稿方法を変更 (新たに用意された API を使っ
                                  て投稿)
                              (3) EUC-JP → Shift_JIS 変換処理でバッファオーバーランが発
                                  生することがある不具合を修正
    Ver 0.29a 2007年 3月16日  (1) proxy情報設定ダイアログが出現したとき、初期設定ファイル
                                  bookey.inf に保存されていた情報が消えてしまうことがある
                                  不具合に対処
                              (2) 実際にはproxyサーバ経由でのアクセスが必須なのに、proxy
                                  サーバは使わない設定にしてしまっている場合、proxy情報の
                                  設定のみいったん初期状態に戻すようにした
    Ver 0.29  2007年 3月15日  (1) proxyサーバに関する設定情報の自動取得に失敗した場合
                                  (proxyサーバを使ってない場合を含む。例えば、Internet 
                                  Explorer, Firefox, Opera の三者以外の Webブラウザが
                                  「通常使うブラウザ」に設定されている場合や、IE をアン
                                  インストールしたにも関わらず、「通常使うブラウザ」の
                                  設定が IE のままになっている場合など)、proxyサーバに関
                                  する設定を手動で設定するためのダイアログを開くようにし
                                  た
                              (2) すでに登録済みのWebページを改めて(上書き)登録しようと
                                  した場合、その WebページのURL に & が含まれると、登録
                                  済みのコメントの内容、タグの内容を拾ってくることができ
                                  ない件に対して、修正を実施
                              (3) 現在、ブックマーク登録・編集ダイアログ経由でブックマー
                                  ク登録作業実行中であっても、ドラッグ・アンド・ドロップ
                                  もしくはコピー・アンド・ペーストで新たな URL を貼り付
                                  けることができるようにした(ブックマーク予定の URL を
                                  キューイングできるようにした[最大64URLまで待ち行列に蓄
                                  積可能])
    Ver 0.28  2007年 3月 6日  (1) MM/Memo のサーバが不調であると判断した場合は、それ以降
                                  (再度 bookey を起動し直すまで)、MM/Memo に登録している
                                  人の数を取得するAPIやタグ候補を取得するAPIの呼び出しを
                                  行なわないようにした
                              (2) タグ候補を抽出するにあたって、新たに「はてなダイアリー
                                  キーワードリンク」に関するAPIを利用するようにした。
                              (3) はてなブックマーク、MM/Memo、はてなダイアリーキーワード
                                  を利用しても、タグ候補の数が十分揃わない場合は、KOSHIAN
                                  を利用するようにした(それでも足りない場合は、今まで通り、
                                  bulkfeedsのAPIを呼び出す)
                              (4) ブックマーク登録ダイアログに、livedoorクリップに登録して
                                  いる人の数も表示するようにした
                              (5) ブックマーク登録ダイアログのニフティクリップのアイコンを
                                  クリップすると、登録しようとしているWebページに関する「ク
                                  リップ情報ページ」を(デフォルトの)ブラウザ経由で閲覧でき
                                  るようにした
                              (6) 登録しようとしているWebページの URL の長さが512バイト以
                                  上のときに、1470.netのタグ候補を取得するAPIを呼び出す処
                                  理、および del.icio.us に登録している人の数を取得する処
                                  理の双方でメモリ破壊が発生する不具合を修正
                              (7) bulkfeeds の特徴語抽出APIを呼び出す直前の文字コード変換
                                  処理でコード変換に失敗した場合に bookey が異常終了する不
                                  具合を修正
                              (8) FC2BOOKMARK からエクスポートした OPML 形式のファイルをイ
                                  ンポートできるようにした
    Ver 0.27  2007年 2月23日  (1) すでに自分自身が「BlogPet気になる記事」に登録済みの URL 
                                  を再度登録しようとした場合、上書き登録してもいいか、確認
                                  した上で上書き登録できるようにした(従来は、「すでに登録済
                                  みである」旨、ダイアログで警告して、登録せずに終了してい
                                  た) [ただし、タイトルを変更しようとした場合は、上書きに失
                                  敗するようになっている]
                              (2) IE または Firefox を使っている環境で、proxyサーバの設定を
                                  残したまま(サーバ名、ポート番号を空欄にしないまま)の状態
                                  で、proxyサーバを使用しない設定に(ブラウザの設定を)変更し
                                  た場合、proxyサーバを使用する設定のままであると bookey が
                                  誤認する不具合を修正。なお、Opera に関しては、IE または
                                  Firefox の設定をそのまま流用している(opera6a.ini では未設
                                  定の)場合のみ、この不具合が発生する。[この「誤認」発生時、
                                  ブックマークの登録、取得、削除、同期等、http/https 通信を
                                  伴う処理はすべて失敗する]
                              (3) 設定画面で「適用」ボタンを押さずに複数のタブを行ったり来た
                                  りすると、以前いたタブで設定した内容が消えてしまう(設定前
                                  の内容に戻ってしまう)不具合に対処。タブを切り替えても内容
                                  を保存するようにした(ただし、「キャンセル」ボタンを押して
                                  設定画面を抜けた場合は、それまでの設定変更内容を設定ファ
                                  イルに反映しない(「適用」ボタンを押した時点の設定内容は設
                                  定ファイルに反映される)
                              (4) はてなブックマーク、Buzzurl、「BlogPet気になる記事」に関
                                  して、登録しようとしているWebページがすでに誰かによって登
                                  録済みの場合、その登録済みのタイトルをそのまま使うか、自
                                  分で指定したタイトルで上書きするか、設定できるようにした。
                                  コマンドライン版の putHB.exe, putBuzzul.exe, putBlogPet.exe
                                  に関しても、-F オプションを追加し、上書き登録することを明
                                  示的に指示できるようにした [-F オプションを指定しない場合
                                  は登録済みのタイトル(が存在すれば)をそのまま使います]
                              (5) ニフティクリップについて、(エントリページのタイトルは共有
                                  されるものの)各自が独自のタイトルを保持できることがわかっ
                                  たため、設定画面から「タイトルの設定」関連ラジオボタンを
                                  削除した (livedoorクリップに関しても、同様の理由ですでに
                                  削除済み)
                              (6) パーセントエンコードもしくはシャープエンコードされている
                                  文字列をデコードする処理で、デコード前の文字列が1024バイ
                                  トより長いと、メモリ領域の破壊が起き(て、bookey が異常終
                                  了す)ることがある不具合を修正
                              (7) POOKMARK Airlines に長い(パーセントエンコード後のサイズが
                                  256バイト以上になる)タイトルの記事を投稿しようとするとサー
                                  バ側からエラーが返ってくる件に対処するため、255バイト以内
                                  におさまるようにタイトルの末尾を削ってから、投稿するように
                                  した
                              (8) すでに登録済みのブックマークをさらに登録しようとしようとし
                                  たとき、Drecom RSS もしくは Flog の少なくともどちらか一方
                                  のカテゴリ(ジャンル)に相当するタグが登録済みのブックマーク
                                  のタグに含まれていない場合に不正なポインタ参照が発生して
                                  bookey が異常終了する不具合に対処した
    Ver 0.26  2007年 2月 5日  (1) IBM の developerworks 関連の Webページの URL の末尾に
                                  ?ca=drs- という文字列が付いている場合、取り除いてからブッ
                                  クマーク登録するようにした
                              (2) すでに自分自身が「はてなブックマーク」に登録済みの URL を
                                  再度登録しようとした場合、登録済みのコメント、タグを取得
                                  し、ブックマーク登録・編集ダイアログに編集可能な形で表示
                                  するようにした
                              (3) すでに自分自身がドリコムRSS(のClip!)に登録済みの URL を
                                  再度登録しようとした場合、上書き登録してもいいか、確認し
                                  た上で上書き登録できるようにした(従来は、「すでに登録済
                                  みである」旨、ダイアログで警告して、登録せずに終了してい
                                  た)
                              (4) すでに自分自身が livedoor クリップに登録済みの URL を再
                                  度登録しようとした場合、上書き登録してもいいか、確認した
                                  上で上書き登録できるようにした(従来は、「すでに登録済み
                                  である」旨、ダイアログで警告して、登録せずに終了していた)
                              (5) 「BlogPet気になる記事」に登録しようとしているWebページの
                                  タイトルをデフォルトのタイトル以外のものにしようとしてい
                                  る場合、その記事をまだ誰も登録していないときに限って、そ
                                  のまま登録できるようにした(すでに誰が別のタイトルもしく
                                  はデフォルトのタイトルで登録している場合は、登録に失敗す
                                  る)
    Ver 0.25a 2007年 2月 1日  (1) 2月1日に実施された Buzzurl の login 直後に表示される画面
                                  の変更の影響で、login成功/失敗判定処理が(実際は login に
                                  成功していても)「login失敗」と判定するようになってしまっ
                                  たため、改修を実施
                              (2) 英語モード時に表示される文言の typo を修正 
    Ver 0.25  2007年 1月31日  (1) 日本語版以外の Windows で起動すると、英語モードで動作す
                                  るようにした(日本語版の Windows で起動した場合は、従来通
                                  り、日本語で表示する)
                              (2) はてなブックマーク、del.icio.us、ニフティクリップ、Blue
                                  Dot について、タグの一括置換機能を実装した
                              (3) はてなブックマーク、del.icio.us、ニフティクリップ につい
                                  て、タグの一括削除機能を実装した
                              (4) 新たに put1470net.exe, putBlogPet.exe, putBlueDot.exe,
                                  putBuzzurl.exe, putDRC.exe, putFlog.exe, putJoltMark.exe,
                                  putLC.exe, putNC.exe, putNewsing.exe, putPookmark.exe を
                                  同梱
                              (5) ブックマーク登録しようとしている記事のタイトル中に ';' 
                                  が含まれる場合、';' の直前までの部分のみがタイトルとして
                                  登録されるという現象が一部のブックマークサービス(Buzzurl
                                  など)で発生している件に関して、対策を実施した
    Ver 0.24b 2007年 1月19日  (1) Vox の記事を「BlogPet 気になる記事」にブックマークしよう
                                  とすると bookey が異常終了する不具合に対処
                              (2) Buzzurl への登録時、タグを指定しても無視されてしまう不具
                                  合に対処
                              (3) 新たに get1470net.exe, getBlogPet.exe, getBlueDot.exe,
                                  getBuzzurl.exe, getLC.exe, getNC.exe, getFlog.exe,
                                  getPookmark.exe, getJoltMark.exe を同梱
                              (4) getDRC.exe の出力する OPML ファイルが文字化けする(UTF-8 
                                  と Shift_JIS が混在することがある)不具合に対処
    Ver 0.24a 2007年 1月13日  JoltMark からのブックマーク取得処理から永久に返ってこなくなる
                              ことがある不具合を修正 (削除のためのブックマーク情報取得処理
                              に関しても同様の不具合があり、修正した。JoltMark の html ファ
                              イルの書き方が変わったのが原因)
    Ver 0.24  2007年 1月11日  (1) ECナビ人気ニュースがリニューアルして Buzzurl になったのに
                                  伴う各種変更、修正を実施
                              (2) Blue Dot の「取得」処理を修正(仕様変更により、全件数取得
                                  処理がうまく動かなくなった)。OPML ファイルへの書き出し時に
                                  文字化けが発生したり、invalid な XML ファイルになってしま
                                  うことがある不具合に関しても修正を実施
    Ver 0.23a 2007年 1月 4日  『実際には処理が終わっているにも関わらず、「○○に登録中……」
                              ダイアログが消えずに残ることがある』不具合(ブックマーク登録処
                              理中に bookey を最小化し、登録処理終了後にウィンドウサイズを
                              元に戻すと「○○に登録中……」ダイアログが残ったままになるこ
                              とが判明)に対処
    Ver 0.23  2006年12月27日  ブックマーク投稿ダイアログに右クリックメニューを導入。指定
                              したブックマークサービスを一時的にブックマーク登録対象から
                              はずしたり、再び登録対象に戻したりできるようにした
    Ver 0.22  2006年12月26日  (1) JoltMark と「BlogPet 気になる記事」の登録、取得、削除、
                                  同期に対応した
                              (2) livedoor クリップから取得した情報を OPML ファイルに書
                                  き出すときの「評価」の値が、「評価」の存在する最初の
                                  ブックマークの「評価」の値と同じ値になってしまう不具
                                  合を修正
                              (3) xmlRPC.dll に組み込む OpenSSL の版数を 0.9.8b から
                                  0.9.8d に変更した (0.9.8a から 0.9.8b へ変更は2006年
                                  5月に実施済み)
    Ver 0.21  2006年12月 8日  (1) livedoor クリップからエクスポートしたファイル(RSS 2.0
                                  形式)を bookey にインポートできるようにした
                              (2) livedoor クリップ、ニフティクリップ、POOKMARK Airkines
                                  に関して、公開・非公開を選択して登録できるようにした
                                  (現時点の bookey では、この3つ以外のソーシャルブックマー
                                   クに関しては、公開・非公開の選択状態に関わらず、常に
                                   「公開」で登録します[はてなブックマークをプライベート
                                   モードで使っている場合は、常に「非公開」で登録します])
                              (3) livedoor クリップ、ニフティクリップ、POOKMARK Airkines
                                  に関して、OPMLファイルへのエクスポート時、公開・非公開
                                  のどちらで登録したブックマークであるかの情報も含めるよ
                                  うにした
                              (4) ローカルOPMLへのブックマーク登録時も、公開・非公開の情
                                  報を含んだ形で登録(書き出し)するようにした
                              (5) 公開・非公開の情報を含んだ OPML ファイルのインポートに
                                  対応した
    Ver 0.20b 2006年12月 5日  NETSCAPE-Bookmark-file-1形式でのエクスポート時、UTF-8 以
                              外に Shift_JIS でのエクスポート(Internet Explorer 向け)
                              もできるようにした
    Ver 0.20a 2006年11月28日  (1) POOKMARK Airlines からのブックマーク取得時、パスワー
                                  ド欄が空白の場合は、指定ユーザの公開状態のブックマー
                                  クを取得できるようにした (本当は今までの版でもできな
                                  いといけなかったんですが、ソースの直し忘れでできない
                                  状態になっていました)
                              (2) POOKMARK Airlines からのブックマーク取得時、コメント
                                  が空のブックマークの取得に失敗する不具合に対処
                              (3) 取得済みブックマークを OPMLファイルに書き出す場合、
                                  「評価」が存在しないブックマークの記事題名が Shift_JIS
                                  で出力されてしまう不具合に対処
                              (4) OPMLファイル、NETSCAPE-Bookmark-file-1形式のhtmlファ
                                  イル、opera6.adr形式のファイルのそれぞれの書き出し時、
                                  すでに同じ名前のファイルが存在するときに上書きしてい
                                  いか、ユーザに尋ねるダイアログが表示されない不具合
                                  に対処
    差し替え版 2006年11月20日 「Ver 0.19  2006年11月16日」の (8) “bulkfeeds.net の形
                              態素解析APIを呼び出す処理でメモリオーバーランが発生する
                              (Shift_JIS → UTF8 変換直後に発生する)ことがある不具合
                              に対処”に関して、対処が十分でなかったことが判明しまし
                              た。例えば
                                 http://www.weathermap.co.jp/hitokuchi_rss/support/2006/11/rss.html
                              をブックマークしようとすると、bookey が異常終了してしま
                              います。この不具合に対処するため xmlRPC.dll に修正を施
                              しました。bookey.exe 本体には修正は行なっていません。    
    Ver 0.20  2006年11月17日  (1) MM/Memo の title 要素互換の形式で「評価」を outline 
                                  要素の title 属性に埋め込んで記録していた従来の方法
                                  をやめ、OPMLの outline 要素に独自属性を追加して、
                                  「評価」を記録するようにした
                              (2) newsing の「○×評価」に関しても、OPML の outline 要
                                  素に独自属性を追加して記録できるようにした(ただし、
                                  newsing からのエクスポートは未対応[将来対応予定])。
                                  ローカルOPMLと newsing が同時投稿対象になっている場
                                  合は、この独自属性を使って、ローカルOPMLファイルに
                                  「○×評価」を記録する
                              (3) 「MM/Memo の title 互換の形式」で表現された title 要
                                  素もしくは title 属性を読み込んだ(インポートした)場
                                  合、通常の形式の title 要素もしくは title 属性に変換
                                  してから、書き出す(エクスポートする)ようにした [「評
                                  価」機能の存在しないソーシャルブックマークサービスへ
                                  の登録(エクスポート)時に title 要素を汚染するのを防止
                                  するのが目的]
    Ver 0.19  2006年11月16日  (1) NETSCAPE互換のブックマークファイル[NETSCAPE-Bookmark-file-1
                                  形式のhtmlファイル]のインポート、エクスポートに対応した
                              (2) Opera 独自のブックマークファイル[opera6.adr ファイル]の
                                  インポート、エクスポートに対応した
                              (3) 2006年10月31日近辺の BlogPeople Tags のログインシーケン
                                  スの仕様変更により BlogPeople Tags への登録および(login
                                  が必要な場合の)取得ができなくなってしまっていたのを、再び
                                  正常に登録、取得ができるように対処した
                              (4) del.icio.us からのブックマーク削除処理で、削除対象のブッ
                                  クマークの URL の長さが 512バイト超の場合、bookey が落ち
                                  てしまう不具合に対処した
                              (5) 「設定ダイアログ」で「1470.netリニューアル版」のタブを選
                                  択したとき、画面の下の方が切れてしまって表示されない不具
                                  合に対処した
                              (6) IE7 との相互運用(ドラッグ・アンド・ドロップによるブック
                                  マークの登録、proxy設定の取得、など)が問題なく行なえるこ
                                  とを確認した
                              (7) はてなブックマークから RSS または Atom フィード形式でエ
                                  クスポートしたファイルを bookey にインポートできるように
                                  した
                              (8) bulkfeeds.net の形態素解析APIを呼び出す処理でメモリオー
                                  バーランが発生する(Shift_JIS → UTF8 変換直後に発生する)
                                  ことがある不具合に対処
                              (9) OPMLファイル、ブックマークファイルなど、ファイルからのイ
                                  ンポート時およびファイルへのエクスポート時にも、処理実行
                                  中ダイアログを出すようにした。また処理実行中に画面を再描
                                  画する必要が発生した場合は、再描画するようにした
    Ver 0.18a 2006年10月28日  ローカルPC上のOPMLファイル(ローカルOPML)へのブックマークの登
                              録に失敗する(ことが多い)不具合に対処
    Ver 0.18  2006年10月27日  (1) ローカルPC上のOPMLファイル(ローカルOPML)に対するブック
                                  マークの登録、取得、削除、同期をサポート
                              (2) OPMLファイルからブックマーク情報を bookey に読み込む処理
                                  でバッファオーバーランが発生する可能性があることが判明し
                                  たため、対策を実施
                              (3) POOKMARK Airlines の html ファイルのフォーマットが変わっ
                                  た影響で取得、削除(に必要な情報の取得)が期待通りに動かな
                                  くなってしまっため、新しいフォーマットに合わせて取得処理
                                  を修正
                              (4) proxy の設定をレジストリ等から読み出す処理を Firefox 2 に
                                  も対応するよう改修した (Internet Explorer 7 に関しては動
                                  作未確認。日本語版の正式なものが出たら、確認する予定)
    Ver 0.17b 2006年10月23日  (1) ブックマーク取得処理以外に関しても、受信バッファオーバー
                                  ランが発生する可能性のある箇所を洗い出し、対策を実施
                              (2) 上記の改修により、2006年10月21日ごろから発生していたECナ
                                  ビ人気ニュースへのブックマーク登録実行時に bookey が異常
                                  終了する(クラッシュする)不具合が発生しなくなったことを確
                                  認
    Ver 0.17a 2006年10月18日  (1) ブックマーク取得処理でバッファオーバーランが発生する(タ
                                  グやコメントが長いとメモリ領域の破壊が起きる)可能性があ
                                  る箇所を洗い出し、対策を実施
                              (2) Blue Dot の「取得」処理を修正、任意のユーザのブックマー
                                  ク(公開範囲が Everyone のもの限定)を取得できるようにした
                              (3) ECナビ人気ニュースのログイン処理に対し、バッファオーバー
                                  ラン対策を実施
    Ver 0.17  2006年10月10日  (1) Blue Dot の「登録」、「取得」、「削除」、「同期」に対応
                                  した
                              (2) 登録済みブックマーク数が多い(約900件以上)場合、del.icio.us
                                  の「取得」(「削除」に必要な情報の「取得」も含む)に失敗
                                  することが多いため、取得しようとしているブックマーク件数
                                  に比例してタイムアウト時間を長くすることで対応(ほとんど
                                  失敗しなくなった)
                              (3) ECナビ人気ニュースの Web ページの文字コードが EUC-JP か
                                  ら UTF-8 に変わったため(ログインに失敗するようになった)、
                                  文字コードに依存する処理を修正
    Ver 0.16  2006年10月 4日  (1) newsing への「登録」(○×評価付き)に対応した
                              (2) POOKMARK Airlines の「登録」、「取得」、「削除」、「同
                                  期」に対応した
                              (3) 同時登録対象の1つに Flogs が入っている場合、ジャンルと
                                  して「漫画/アニメ」を選択した場合、他の同時登録対象の
                                  ソーシャルブックサービスに対して cartoon タグを付ける
                                  はずが catoon タグを付けていた(綴り誤り)不具合を修正
    Ver 0.15a 2006年 9月28日 (未公開)
                              (1) ブックマーク登録内容編集ダイアログで「評価」を指定でき
                                  るようにした。この「評価」は、1470.netリニューアル版、
                                  MM/Memo、BlogPeople Tags、livedoor Bookmark (のうち同
                                  時登録対象に設定済みのもの)に対して同時に同じ値で登録
                                  される
                              (2) 9月8日に出現したアマゾンの新しいURLパターン2つに対応
                              (3) 「はてなブックマーク」のコレクションや「1470.netリニュー
                                  アル版」のMONOに登録する場合、登録失敗を防ぐため、ア
                                  マゾンのURLを従来のURLに変換してから登録するようにし
                                  た
                              (4) MM/Memo の「取得」処理でメモリオーバーランが発生する
                                  可能性のある箇所に修正を施し、メモリオーバーランが起
                                  きないようにした
                              (5) proxyサーバの設定情報を各ブラウザの設定ファイルから取
                                  得する処理を修正。Opera 9.x にも対応した
    Ver 0.15  2006年 9月 6日  (1) ドリコムRSS の Clip! の「削除」に対応した
                              (2) 「削除ダイアログ」に「1個前に戻る」ボタンを追加した
                              (3) 「同期ダイアログ」に「1個前に戻る」ボタンを追加した
                              (4) アマゾンの商品ページの URL のバリエーション増加に伴い、
                                  はてなブックマークの「コレクション」、1470.netリニュー
                                  アル版の「MONO」への登録を行なう処理を書き直した
                                  (なお、登録しようとしている URL に含まれる文字列によっ
                                   ては MONO への登録が行なわれないことがあります[1470.net
                                   側の問題?])
                              (5) cookie 関係の処理でメモリオーバーラン、スタックフレーム
                                  破壊が発生することがある不具合に対処した
                              (6) 2006年8月24日ごろから、ニフィティクリップへの登録時に
                                  「登録に失敗しました」という警告が出る(が実際は登録には
                                  成功している)ようになってしまった件に対処した
                              (7) 削除処理を実行するための事前のブックマーク情報取得処理
                                  実行中も、画面の再描画やフォーカス制御を行なうようにし
                                  た
                              (8) ドリコムRSS の Clip! からブックマーク(クリップ)を吸い出
                                  すコマンドラインツール getDRC.exe を新たに同梱するよう
                                  にした
    Ver 0.14  2006年 8月26日  (1) はてな認証API経由での1470.netリニューアル版へのアクセス
                                  に対応した
                              (2) MM/Memo の「削除」に失敗する(あるいは処理途中でメモリ
                                  オーバーランが発生し、bookey がクラッシュする)ように
                                  なってしまっていたのを修正 (MM/Memo の html の内容が
                                  変わった?)
                              (3) 1470.netリニューアル版の「取得」「同期」、「削除」に
                                  対応した
                              (4) どのブックマークを削除するか選択するダイアログ(が2つ
                                  あったのを1つにまとめた、等)のデザインを変更
                              (5) はてな認証対応に伴い、各種ダイアログデザイン、ユーザ
                                  インターフェイスを修正
    Ver 0.13a 2006年 8月18日  (1) del.icio.us の API 改訂(2006年8月9日)に伴い、新API を
                                  使うようにした (今のところ、新旧両方のAPIが並存してい
                                  るが、いずれ旧APIは使えなくなるものと思われる)
                              (2) ECナビ人気ニュースの各記者ごとのページの html の内容が
                                  変わった影響で、「ブックマークの取得」が失敗するように
                                  なってしまった(2006年8月17日)ため、新しい内容に合わせて
                                  「取得」処理を書き直した
                              (3) ECナビ人気ニュースが「ブックマークの削除」をサポートす
                                  るようになった(2006年8月9日)ので、bookey からも「削除」
                                  できるようにしてみた
    Ver 0.13  2006年 7月31日  (1) ECナビ人気ニュース、ニフティクリップ、1470.netリニュー
                                  アル版への登録がうまくいかないことがある不具合に対処し
                                  た(完全に bookey のバグ)
                              (2) 上記とは別に、bookey で一度1470.netリニューアル版に登
                                  録した後に、ブラウザ等で1470.netリニューアル版のマイ
                                  ページにアクセスすると、その後、bookey から1470.netリ
                                  ニューアル版への登録が失敗する可能性があるため、対策を
                                  実施
                              (3) 設定ダイアログを導入。ユーザ名やパスワード以外の設定項
                                  目も同時に設定できるようにした
                              (4) 2006年7月31日のlivedoorのログインページの変更により、
                                  livedoorクリップの登録、取得処理(から呼び出しているロ
                                  グイン処理)が異常終了するようになってしまったため、ロ
                                  グイン処理を修正
                              (5) ドリコムRSSのログイン失敗時のリトライ回数を3回から5回
                                  に変更
                              (6) 1470.netリニューアル版のログイン失敗時のリトライ周期を
                                  2秒に変更
                              (7) ThinkIT の(メールマガジンで使用されている)リダイレクタ
                                  に対応
    Ver 0.12  2006年 7月25日  ドリコム関連のサービスがすべてドリコムアカウント経由での認
                              証を利用するようになった(2006年7月25日から)のに伴い、ドリ
                              コムRSSのログイン処理をドリコムアカウントに対応するよう変
                              更した。(注意: 本日以降、ドリコムRSS(のClip!)の登録、取得、
                              同期を行なう前に、ドリコムアカウントへの移行手続きを行なっ
                              ておいてください。手続きをしておかないと、bookey による登
                              録、取得、同期が実行できません。ご了承ください)
    Ver 0.11d 2006年 7月24日  (1) livedoorクリップの削除処理も、livedoorクリップのWebペー
                                  ジのフォーマット変更に対応
                              (2) プライベートモードのクリップが存在するlivedoorクリップ
                                  に対する取得処理(削除処理のための取得もを含む)実行結果
                                  の内容がおかしくなる(最初のプライベートモードのクリップ
                                  が抜ける、クリップの最終ページを重複してリストに入れて
                                  しまう)不具合に対する修正を実施
                              (3) はてなブックマーク取得時に、タイトルの先頭に改行が含ま
                                  れる場合があるのを考慮し忘れていたため、対処を実施
                              (4) タイトルの先頭に改行が含まれている OPML ファイルを読み
                                  込むと bookey が異常終了することがある現象に対処
                              (5) はてなブックマークから取得したブックマークのタイトルが
                                  文字化けを起こすことがある(iconv で変換不可能な文字が含
                                  まれる場合に作動する bookey 内のリカバリ処理に不完全な
                                  箇所が存在するため、文字化けが発生することがある)現象に
                                  対処
    Ver 0.11c 2006年 7月22日  (1) livedoorクリップのWebページのフォーマット変更により、
                                  ブックマークを取得できなくなってしまった(最初の20件のみ
                                  しか取得できなくなってしまった)ため、取得処理を修正し、
                                  取得できるようにした(削除処理にも同様の対処が必要だが未
                                  対応 → 0.11d 版で対応する予定)
                              (2) ブックマークの取得に失敗した場合、全何件中の何件までは
                                  取得に成功したか表示する処理を、BlogPeople Tags、livedoor
                                  クリップ、ECナビ人気ニュース、ニフティクリップの取得処
                                  理にも追加した
    Ver 0.11b 2006年 7月20日  (1) MyClip! 関連の処理を削除した(getMyclip.exe の同梱も中止。
                                  clcoo.exe 内の MyClip! 関連処理はそのまま残してある)
                              (2) del.icio.us からのブックマーク取得(同期、削除の準備のた
                                  めの取得も含む)に失敗した場合についても、何件目まで取得
                                  に成功しているか、表示するようにした(ただし、実際には、
                                  del.icio.us に関しては API の仕様上、1件も取得できずに
                                  終了するか、全件取得に成功するかのどちらかしかあり得な
                                  いので、あまり意味がないともいえる)
                              (3) livedoorクリップとニフティクリップの取得処理の双方にメ
                                  モリリークが発生する可能性があることが判明したため、修
                                  正を実施した
    Ver 0.11a 2006年 7月18日  (1) はてなブックマークの登録時、取得時の挙動が変わった(今ま
                                  で XML invalid だったのが valid になった)のに伴い、タイ
                                  トル、コメントのエンコード、デコード処理を修正。他のブッ
                                  クマークサービスへのエクスポート(他のブックマークのイン
                                  ポート)処理も修正した
                              (2) 1470.netリニューアル版の MONO の登録に対応した
                              (3) MM/Memo、BlogPeople Tags、livedoorクリップのうちの任意の
                                  ブックマークを1470.netリニューアル版にインポートするとき、
                                  評価(レート)も取り込むようにした
                              (4) MM/Memo のメモを 1470.netリニューアル版にインポートする
                                  とき、MM/Memo の「メモ種別」を1470.netリニューアル版のグ
                                  ループとして取り込むようにした
                              (5) ドリコムRSS へのログイン失敗時、最大3回までログインをや
                                  り直すようにした(ログイン失敗頻度が高いため)
                              (6) ドリコムRSS、BlogPeople Tags、livedoorクリップ、ECナビ
                                  人気ニュース、ニフティクリップ、Flog、1470.netリニュー
                                  アル版へのログイン失敗時、ログインに失敗したことを示す
                                  ダイアログを表示するようにした
                              (7) はてなブックマークのコレクションへの追加時、デバッグ用の
                                  ファイル(hatena.htmlという名前のファイル)を生成する処理
                                  が生きていることが判明、処理を削除した
                              (8) MM/Memo と 1470.netリニューアル版への同時登録実行時、
                                  MM/Memo のみにしか登録できないことがある現象に対して対
                                  策を実施(同時登録実行時は cookie をその都度取得し直すよ
                                  うにした)
    Ver 0.11  2006年 7月15日  (1) はてなブックマークからのブックマーク取得(同期、削除の準
                                  備のための取得も含む)に失敗した場合、何件目までは取得に
                                  成功しているか、表示するようにしてみた
                              (2) livedoorクリップ、ニフティクリップの取得、同期、削除に対
                                  応した
                              (3) ドリコムRSS(のClip!)、ECナビ人気ニュースの取得、同期に対
                                  応した
                              (4) 1470.netリニューアル版への登録に対応した(現時点では、
                                  TypeKeyによる認証のみサポート。はてな認証API経由でのアク
                                  セスにはまだ対応していない)
                              (5) 登録中、取得中など進捗状況を表示するダイアログが、別のダ
                                  イアログの後ろに隠れて見えなくなってしまうことがある現象
                                  に対処。また、砂時計カーソルが出ない場合があったため、確
                                  実に砂時計カーソルを出すようにした
                              (6) MM/Memo、BlogPeople Tags、livedoorクリップのうちの任意の
                                  二者間で同期を行なう場合、評価(レート)も移行できるように
                                  した
                              (7) はてなブックマークに登録済みのURLをさらにはてなブックマー
                                  クに登録(二重登録)しようとした場合、後から登録しようとし
                                  た内容で上書きするようにした(以前のはてなブックマークの挙
                                  動を再現するようにした)
                              (8) OPMLファイル出力時、XML としては invalid なものを出力して
                                  しまう場合があり、そのうちのいくつかについて、invalid にな
                                  らないよう対策を実施した(実体参照を使うのは必要最小限にす
                                  る、など)。この対策により、Ver0.11 以前の bookey で出力し
                                  た OPML (のうち、XML invalid なもの)を、本バージョンの
                                  bookey で読み直した後、改めて出力することで、valid な XML
                                  に変換できる可能性がある
                              (9) 「ブックマーク登録者数を表示する」機能が ON のとき、ECナビ
                                  人気ニュースへの登録者数も表示するようにした
    Ver 0.10a 2006年 6月30日  (1) 「ブックマーク登録者数を表示する」機能が ON のとき、かつ
                                  hatena exist API によるブックマーク登録者数が取得できな
                                  かった場合、はてなブックマークのエントリページを取得して
                                  ブックマーク登録者数を取得するようにしているところ、当該
                                  エントリページが256KBより大きいとき、bookey がクラッシュ
                                  する不具合に対処した
                              (2) ECナビ人気ニュースの登録に対応した
                              (3) ニフティクリップの登録に対応した
                              (4) charset が ISO-2022-JP な Webページも、livedoorクリップに
                                  登録できるように修正した
                              (5) タグの区切りの空白文字が複数個連続しているときに、はてな
                                  ブックマークにタグが全く反映されずに登録されてしまう不具
                                  合に対処した
                              (6) タグ候補をはてなブックマークのエントリページから取得する
                                  とき、複数人によって使用されているタグのみをタグ候補とす
                                  るよう変更した
    Ver 0.10  2006年 6月29日  (1) Flog の取得、削除、同期に対応した
                              (2) livedoor クリップの登録に対応した
                              (3) コメントに改行が含まれる場合、はてなブックマークに登録時、
                                  最後の改行以降の文字列のみがコメントになり、タグは1つも反
                                  映されないという現象に対処した
                              (4) charset が Shift_JIS 以外のWebページでかつタイトルの長さが
                                  128バイトより長い場合、MM/Memo への登録が失敗するか、タイ
                                  トルが空の状態で登録されてしまう不具合に対処した
                              (5) すでに誰かによって登録済みのブックマークを Flog に登録し
                                  ようとするとエラーになる現象に対処した
                              (6) 登録ブックマーク数が1000件以上ある場合、BlogPeople Tags 
                                  から取得(エクスポート)できるブックマークの数が常に1000件
                                  以下になる不具合に対処した
                              (7) 登録しようとしているWebページをすでにブックマークに登録
                                  している人の数(はてなブックマーク、del.icio.us、MM/Memo)
                                  を表示する機能を追加した(デフォルトは表示しない)
                              (8) bookey のドラッグアンドドロップ可能なダイアログの面積を
                                  少し小さくしてみた
                              (9) ブックマーク登録内容編集ダイアログに、どのブックマークへ
                                  の登録機能が ON なのか OFF なのか見ることができるように
                                  した(各ブックマークサービスを象徴するアイコンにマウスカー
                                  ソルを持っていくと、ON/OFF状態を示すツールチップが表示さ
                                  れる)
                              (10) ブックマーク登録中、取得中、同期中など、時間がかかる処理
                                   実行中でも定期的に画面の再描画が必要かどうか調べて、必要
                                   なら再描画するようにしてみた(ダイアログのタイトルに「応
                                   答なし」と表示される状況を減らすことができた)
                              (11) その他、メモリオーバーフロー、バッファオーバーランが発生
                                   する可能性のある箇所に対策を施した
    Ver 0.09  2006年 5月31日  (1) Flog への登録に対応した
                              (2) codezine.jp, markezine.jp のリダイレクタに対応した
                              (3) URL の末尾に ?fr=rdf が含まれる場合、この文字列を取り除い
                                  てから、ブックマークに登録するようにした
                              (4) (MM/Memo, BlogPeople Tags, JoltMark などの)「評価」機能を
                                  利用できるようにするための準備として、ブックマーク登録ダ
                                  イアログに「評価」入力用のボタンを設置してみた(まだ、ボタ
                                  ンは押せない)
    Ver 0.08e 2006年 5月25日  (1) MM/Memo へ「同期」しようとしているWebページが Amazon.co.jp
                                  の個別商品詳細解説ページの場合についても、ASIN の比較によ
                                  り、当該Webページが すでに MM/Memo に登録されているかどう
                                  かを判断するようにした
                              (2) feedburner.jp, google.com, pheedo.jp, neowing.co.jp
                                  のリダイレクタが使われている場合、リダイレクト先のページ
                                  の URL を実際のブックマーク対象とするようにした(リダイレ
                                  クト先でさらに別のリダイレクタが使われている場合は、最終
                                   的なリダイレクト先をブックマーク対象 URL とする)
                              (3) URL の末尾に ?from=top, &from=rss, ?topic=1 が含まれる場
                                  合、これらの文字列を取り除いてから、ブックマークに登録す
                                  るようにした
    Ver 0.08d 2006年 5月24日  (1) MM/Memo へ「同期」しようとしているWebページが Amazon.co.jp
                                  の個別商品ページの場合、同期元と同期先の URL の比較では
                                  なく ASIN の比較により、当該Webページが すでに MM/Memo 
                                  に登録されているかどうかを判断するようにした
                              (2) 「同期」しようとしているWebページの URL に &amp; が含ま
                                  れる場合は、&amp; を & に置換してから、登録するようにし
                                  た
    Ver 0.08c 2006年 5月23日  (1) BlogPeople Tags の取得処理と登録処理の双方にメモリオー
                                  バーランが発生する可能性があることが判明。修正を実施
                              (2) 「同期」対象のブックマーク情報の取得に失敗した場合は、
                                  再度取得を試みるかどうか、尋ねるようにした
                              (3) MM/Memo に対する操作を行なうときに、毎回 TypeKey サーバ
                                  に login し直していたのを、一定時間経過するまでは login
                                  し直さずに済むように修正した(cookie をキャッシュに保持
                                  することで対応)
                              (4) ブックマークに登録しようとしているWebページがすでに誰か
                                  によって「はてなブックマーク」に登録済みの場合、当該ブッ
                                  クマークのエントリページから、すでに使用されているタグ
                                  一覧を取得し、タグ候補として採用するようにした
    Ver 0.08b 2006年 5月19日  (1) 5月13日以降、BlogPeople Tags に登録できなくなってしまっ
                                  たのを、登録できるように対処 (cookie 回りの処理を新しい
                                  仕様に合わせた)
                              (2) ブックマークの「同期」機能で、すでに登録されているにも関
                                  らず、未登録だと判定して何回でも登録(同期)しようとしてし
                                  まうことがある(URL に数値参照が含まれる場合、16進表記の
                                  大文字小文字の区別をしてはいけないのに、区別してしまって
                                  いた)のを修正
                              (3) bulkfeeds API を呼び出す処理(以外でも発生する可能性があ
                                  る)で、メモリの確保量が少なすぎてメモリオーバーランが起
                                  きることがあった不具合[例えば、使っている tag が多い人の
                                  はてなブックマークトップページをブックマークしようとする
                                  と発生]に対処(修正したのは URL エンコードを行なう処理)
                              (4) MSN毎日新聞のRSS経由で得た URL を登録する場合、末尾につい
                                  ている
                                    ?in=rssw
                                  を取り除いてから、ブックマークに登録するようにした
    Ver 0.08a 2006年 4月 7日  (1) 「ブックマーク管理ツール」ダイアログの方も、ドリコムRSS
                                  の Clip! への登録(インポート)に対応した
                              (2) はてなブックマークの「コレクション」への追加ができなくなっ
                                  てしまった(たぶん、4月6日の夜遅くに「はてなブックマーク」
                                  の微妙な仕様変更があったものと思われる)のを再び追加できる
                                  ように修正した
    Ver 0.08  2006年 4月 6日  (1) ドリコムRSSの Clip! への登録に対応してみた
                              (2) はてなブックマークの「コレクション」への追加に対応した
    Ver 0.07b 2006年 3月27日  (1) UTF-8 で 0xe2-0x80-0x94, 0xe2-0x88-0x92, 0xe2-0xbc-0x8d
                                  のいずれかの文字が5個以上ある場合に「UTF-8 → Shift_JIS
                                  変換処理」で stack overflow が発生して、bookey.exe が強
                                  制終了してしまう不具合に対処
                              (2) ブックマーク登録ダイアログで、URL を編集しようとすると
                                  stack overflow が発生して、bookey.exe が強制終了してしま
                                  う不具合に対処
                              (3) ブックマーク登録ダイアログで、タイトル、タグを編集しよう
                                  とすると stack overflow が発生して、bookey.exe が強制終
                                  了してしまうことがある不具合に対処
                              (4) ブックマーク登録スレッドで表示する「ブックマーク登録中」
                                  ダイアログのスレッド構成を変更 (スレッドを1個減らした)
    Ver 0.07a 2006年 3月13日  (1) 同期機能を使って、MM/Memo のブックマークを他のブックマー
                                  クへコピーしようとすると文字化けする不具合を修正
                              (2) 誰かによってすでに「はてなブックマーク」に登録済みのWeb
                                  ページを登録しようとしたとき、当該Webページの charset が
                                  EUC-JP のとき文字化けが発生する現象に対処
                              (3) タグ候補の表示をする/しない を選択できるようにした
                              (4) FeedBurner もしくは Yahoo! Japan の RSS から取得した URL
                                  をブックマークする場合、FeedBurner もしくは Yahoo! Japan
                                  のリダイレクタが間にはさまっている場合は、リダイレクト先
                                  (要するに本当にブックマークしたいWeb)のURLをブックマーク
                                  対象とするようにした
                              (5) 1470.net のサービス停止中にブックマークをしようとすると、
                                  いちばん最初のタグ候補が ishinao氏の tdiary のトップペー
                                  ジの URL になる現象に対処
    Ver 0.07  2006年 3月10日  (1) MM/Memo、BlogPeople Tags の同期もサポート
                              (2) タグ候補を抽出するための API として、1470.net 提供の API
                                  以外に Bulkfeeds の特徴語抽出 API も併用するようにした
                              (3) del.icio.us に登録する title は実体参照や数値参照を使用せ
                                  ず、生 UTF-8 を使うようにした (はてなブックマークに登録す
                                  る title は、従来通り、必要に応じて、実体参照を使用する)
                              (4) MM/Memo および BlogPeople Tags に登録する title は、
                                  Shift_JIS あるいは EUC-JP では表現できない文字に関して、
                                  代替文字列(例えば、"&copy;" の代替文字列は "(c)")に置換
                                  してから登録を実行するようにした
                              (5) 各ブックマークサービスのパスワード欄が空白になってしまう
                                  (RSAエンコード済みのパスワードのデコードに失敗することが
                                   あり、失敗した場合に空白になってしまう)現象に対する対策
                                  として、エンコード時にデコードできることを確認してから設
                                  定ファイルに保存するようにした(デコードに失敗する場合は
                                  key (および salt) を変えてエンコードし直す。デコードに成
                                  功するまで試行を繰り返す)。[当方の OpenSSL の使い方に問
                                  題がある、もしくは OpenSSL 自体の不具合のどちらかが原因。
                                  いまのところ、原因がはっきりしないので、暫定対策としてデ
                                  コードに成功するパターンが見つかるまでエンコードをやり直
                                  すことにした]
    Ver 0.06d 2006年 2月 8日  (1) ブックマーク間の同期を取る指示を出す画面のデザインを変更
                                  (はてなブックマークとdel.icio.usの二者間以外の同期にも対応
                                   する準備 → 0.07版で正式対応する予定)
                              (2) del.icio.us に約3000件以上ブックマーク済みの場合、全ブック
                                  マーク取得処理でメモリ破壊が発生する不具合に対処
                              (3) 登録しようとしているWebページを誰かがすでに「はてなブック
                                  マーク」に登録済みの場合、タイトルは「はてなブックマーク」
                                  登録済みのものを採用するようにした
                              (4) 登録しようとしているWebページの title 要素に html タグが包
                                  含されている場合(例えば goo ブログ)、それらのタグを除去した
                                  ものをタイトルとして取り込むようにした
                              (5) del.icio.us から取得したブックマークコメント(をはてなブック
                                  マークにインポートするときなどに文字化けが発生することがあ
                                  る)の文字化け対策として、文字化けの原因になる文字を取り去る
                                  ようにしてみた
    Ver 0.06c 2005年12月22日  (1) コメント文字列が UTF-8 で255バイトより長いとき、(Webブラウ
                                  ザでの閲覧時に)del.icio.usのコメント欄が破壊された状態で表
                                  示されることが判明。コメント文字列が UTF-8 で255バイト(文
                                  字列が全て漢字で構成されるという仮定で Shift_JIS なら170バ
                                  イト)より長い場合は、あふれた部分を切り捨てた状態で
                                  del.icio.us に登録(投稿)するようにした
                              (2) 登録しようとしている Web ページの title 要素に余分な white
                                  space (空白、タブ、改行)が含まれる場合は削除するようにした
    Ver 0.06b 2005年12月 7日  (1) 文字列長が20バイトより大きいタグ候補を20バイト以内に丸める
                                  処理の不具合を修正
                              (2) MM/Memo と BlogPeople Tags へブックマークを登録する処理で、
                                  登録しようとしている Web ページのタイトルに"『" と "』" が
                                  含まれる場合、"『" と "』"に囲まれた部分をタイトルとして登
                                  録してしまう不具合に対処 (MM/Memo形式のタイトルに変換済み
                                  であると誤認識してしまっていた)
    Ver 0.06a 2005年12月 1日  (1) 文字列長が20バイト(10文字)より大きなタグ候補が存在する場合、
                                  エラーダイアログが出て、先に進めなくなる不具合に対処
                              (2) タグ入力欄で空白文字が2個以上連続する場合、はてなブックマー
                                  クへの登録時に [] という空タグ(?)ができてしまう現象に対処
                              (3) タグ候補選択時、タグ入力欄にキャレットが存在する場合、キャ
                                  レットの位置がタグ入力欄の先頭に飛んでしまう現象に対処
    Ver 0.06  2005年12月 1日  (1) はてなブックマークの仕様変更(2005年11月29日付け)に対応
                                  なお、はてなブックマークの新しい仕様では、タグは最大10個ま
                                  で、コメントは最大100文字までとなっている。他のソーシャル
                                  ブックマークについては、さらに多くのタグ、長いコメントを
                                  登録できるものもある。
                              (2) 登録しようとしている Web ページについて、タグの候補を最大
                                  20個表示するようにした。タグ候補をクリックすることで、タ
                                  グを選択することができる。
    Ver 0.05  2005年11月13日  (1) BlogPeple Tags と MM/Mmeo の削除をサポート
                              (2) UTF-8 では表現可能ではあるが Shift_JIS や EUC-JP では表現
                                  できない文字に関して文字化け等の不具合が発生する件に対し、
                                  Shift_JIS や EUC-JP でも表現可能な別の文字(列)に変換するこ
                                  とでとりあえずしのぐことにした
                              (3) BlogPeople Tags から読み出したブックマークに強制的に BP_TAGS
                                  というタグを付けていたのを、付けないようにした
                              (4) ブックマークの取得、登録、削除、同期の各処理の進行状況を表
                                  示するダイアログを追加した
                              (5) BlogPeople Tags で評価(マイレート)が付加されているブックマー
                                  クについて、MM/Memo 互換の形式で OPML ファイルに記録するよ
                                  うにした
                              (6) BlogPeople IB から読み出したブックマークに強制的に BPIB とい
                                  うタグを付けていたのを、付けないようにした
                              (7) ドラッグ&ドロップで取り込んだ URL の末尾に ?ref=rss や ?ref=atom
                                  や ?from=rss など余分な文字列が付いている場合は、その文字列を
                                  取り除いた上でブックマーク対象 URL とするようにした
                              (8) bookey.exe を二重起動できないようにした
                              (9) MFC/afx の初期化処理でレジストリを書き換えて(キーを追加して)
                                  しまう可能性のあるコードを削除した
                              (10) MM/Memo のブックマークを OPML ファイルとして出力する処理で、
                                   タグの区切り用の空白文字が余分に入ってしまう不具合を修正した
                              (11) MM/Memo のブックマークを OPML ファイルとして出力し、その OPML
                                   ファイルを MM/Memo に取り込み直すと、memo_kind が反映されず
                                   に消えてしまう不具合を修正した
                              (12) 登録しようとしているブックマークの「タイトル」、「コメント」、
                                   「タグ」のいずれかが空のとき、ゴミが入ってしまうことがある不
                                   具合を修正した
                              (13) xmlRPC.dll に組み込む OpenSSL の版数を 0.9.8 から 0.9.8a に変
                                   更した
                              (14) Firefox の設定ファイルをデフォルトの場所以外に移動している場
                                   合でも、proxy設定を取得できるようにした
    Ver 0.04b 2005年10月29日  (1) 設定を何度も変更しているうちに設定ファイルの保存内容が破壊
                                  されることがある不具合に対処
                              (2) ISO-8859-1 の 0xA0 ～ 0xFF に相当する文字が Web ページの 
                                  title に含まれる場合、当該 Web ページをブックマークレット
                                  等(要するに bookey 以外)で登録した後、bookey で取得すると
                                  title が空になってしまう不具合に対処
                              (3) 上記を受けて、ブックマーク取得時以外についても、ISO-8859-1
                                  の 0xA0 ～ 0xFF の取り扱い方法を検討、暫定的な対処を実施
                                  (課題: Web ページの charset が Shift_JIS のいわゆる「半角
                                   カナ」と誤認識する可能性が残っている)
    Ver 0.04a 2005年10月25日  (1) ブックマークの登録失敗時にボタンの押せない、あるいは姿の見
                                  えないメッセージボックスが無限に増殖する不具合(GUI版のみで
                                  発生する不具合)を修正
                              (2) MM/Memo にアマゾンの個別商品ページを登録しようとすると、常
                                  に登録に失敗する不具合を修正
                              (3) MM/Memo に期待したのとは違うタイトルでブックマークが登録さ
                                  れてしまうことがある不具合を修正 (ただし、例外的に、タイト
                                  ルが 128バイトより大きい場合は、あふれた部分を切り捨ててか
                                  ら登録する)
    Ver 0.04  2005年10月25日  (1) MM/Mmeo と BlogPeople Tags へのブックマークの登録
                              (2) MM/Memo からのブックマークの吸出しに対応
                              (3) はてな投げ銭(はてなポイントの送信)に対応
                              (4) インターネットショートカットのドラッグに対応
                              (5) クリップボードからの取り込みに対応
                              (6) その他、バグフィックス
                              (7) アイコンを MFC デフォルトのものから、独自のものに変えた
                              (8) コマンドラインツール群も同梱するようにした
                              (9) 参考としてソース(の大部分)も同梱するようにした(ビルド環境は
                                  未添付)
    Ver 0.03  2005年10月16日  最初の公開版 「観測気球」にて公開
                              はてなブックマークとdel.icio.usへの同時ブックマーク登録をサポート
    Ver 0.02  2005年10月 7日  はてなブックマークとdel.icio.usの同期をサポート
    Ver 0.01  2005年 9月30日  最初の版 ブックマークの取得、登録、削除をサポート

$Header: /comm/bookey/readme.txt 5     09/06/22 22:05 tsupo $
