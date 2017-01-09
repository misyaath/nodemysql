{
  "targets": [
    {
      "target_name": "nodemysql",
      "sources": ["Main.cpp","common.cpp"],
      'link_settings': {
        'conditions': [
       {
          'libraries': [
            '<!@(mysql_config --libs_r)'
          ],
        }],
        ['OS=="mac"', {
          # cflags on OS X are stupid and have to be defined like this
          'xcode_settings': {
            'OTHER_CFLAGS': [
              '<!@(mysql_config --cflags)'
            ]
          }
        }, {
          'cflags': [
            '<!@(mysql_config --cflags)'
          ],
        }]
      ]
      },
      "include_dirs": [""],
    }
  ]
}
