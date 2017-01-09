{
  "targets": [
    {
      "target_name": "nodemysql",
      "sources": ["Main.cpp","common.cpp"],
      'link_settings': {
        'libraries': [
          'F:/cpp/NodeSql/middleware/mysql-connector-c/lib/libmysql.lib',
         
        ],
      },
      "include_dirs": ["F:/cpp/NodeSql/middleware/mysql-connector-c/include"],
    }
  ]
}
