{
  "targets": [
    {
      "target_name": "nodemysql",
      "sources": ["Main.cpp","common.cpp"],
      'link_settings': {
        'libraries': [
          'PATH_TO_MYSQL_C_CONNECTOR/lib/libmysql.lib',
         
        ],
      },
      "include_dirs": ["PATH_TO_MYSQL_C_CONNECTOR/include"],
    }
  ]
}
