{
  "targets": [
    {
      "target_name": "greet",
      "cflags!": [ "-fno-exceptions -I./home/casne/greeting/src/include -locxbpeng -locxbpapi -locxcnapi -lpthread" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/show_chassis.cpp",
        "./src/index.cpp",
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/home/casne/greeting/src/include"
      ],
      'libraries': [
        '-locxbpeng', '-locxbpapi', '-locxcnapi'
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}