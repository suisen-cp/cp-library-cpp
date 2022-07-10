# テストファイルを書いていて困ったときに見るやつ

## 誤差ジャッジ

`#define ERROR <許容誤差>` を書く。

## `#define problem "..."` の例外

AtCoder の問題を verify に用いる場合は例外がそこそこあるので注意。[dropbox](https://www.dropbox.com/sh/arnpe0ef5wds8cv/AAAk_SECQ2Nc6SVGii3rHX6Fa?dl=0) 上のパスに準拠して書かなければならない。

- ABC233 以降の Ex 問題
  
  H 問題が Ex へと改称された ABC 233 以降、問題の URL は `https://atcoder.jp/contests/abcXXX/tasks/abcXXX_h` のままだが、dropbox 上では Ex へと名称が変更されているので、`https://atcoder.jp/contests/abcXXX/tasks/abcXXX_Ex` と書く必要がある

- ABC/ARC 同時開催
  
  忘れたけどこれも変だったはず

- 典型 90 問
  
  URL は `a,b,...,z,aa,ab,...` と番号が振られているが、dropbox 上では `001,002,...,090` と振られている
