#include "schrift.h"

struct Font {
  SFT sft = {NULL, 12, 12, 0, 0, SFT_DOWNWARD_Y|SFT_RENDER_IMAGE};
  Font(const char* fontfile, uint16_t size) {
    if((sft.font = sft_loadfile(fontfile)) == NULL) {
      printf("\e[31m[ERROR] Failed to load %s\e[0m\n", fontfile);
      return;
    }
    set_size(size);
  } 

  ~Font() {
    sft_freefont(sft.font);
  }

  void set_size(uint16_t size) {
    sft.xScale = size;
    sft.yScale = size;
  }
};
