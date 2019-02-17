{
  "targets": [
    {
      "target_name": "okhound",
      "libraries": [ "../libPhraseSpotter.a" ],
      "include_dirs": [ "." ],
      "sources": [ "OkHound.cc" ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": ["okhound"],
      "copies": [{
        "files": ["<(PRODUCT_DIR)/okhound.node"],
        "destination": "."
      }]
    }
  ]
}