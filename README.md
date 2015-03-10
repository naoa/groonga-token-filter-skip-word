# token filter plugin for Groonga

## Token Filters

### ``TokenFilterSkipWord``

``skip_words``テーブルにあるキーと一致するトークンを``GRN_TOKEN_SKIP``で飛ばします。


### ``TokenFilterSkipWordWithPosition``

``skip_word_with_positions``テーブルにあるキーと一致するトークンを``GRN_TOKEN_SKIP_WITH_POSITION``で飛ばします。


### Source install

Build this tokenizer.

    % sh autogen.sh
    % ./configure
    % make
    % sudo make install

## Dependencies

* Groonga >= 4.0.7

Install ``groonga-devel`` in CentOS/Fedora. Install ``libgroonga-dev`` in Debian/Ubuntu.

See http://groonga.org/docs/install.html

## Usage

Firstly, register `token_filters/skip_word`

## Author

* Naoya Murakami <naoya@createfield.com>

## License

LGPL 2.1. See COPYING for details.

This program is the same license as Groonga.
