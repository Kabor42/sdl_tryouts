#include "include/dept_hist.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include <astra/astra.hpp>

class MyFrameListener : public astra::FrameListener {
private:
  using buffer_ptr = std::unique_ptr<int16_t[]>;
  buffer_ptr buffer_;
  uint32_t last_width{0};
  uint32_t last_height{0};
  DepthHist *dh{NULL};

public:
  MyFrameListener(DepthHist *dh) { this->dh = dh; }
  virtual void on_frame_ready(astra::StreamReader &reader,
                              astra::Frame &frame) override {
    const astra::DepthFrame depthFrame = frame.get<astra::DepthFrame>();
    auto depthStream = reader.stream<astra::DepthStream>();

    astra::CoordinateMapper mapper = depthStream.coordinateMapper();

    if (depthFrame.is_valid()) {
      const short *depthData = depthFrame.data();
      uint32_t width = depthFrame.width();
      uint32_t height = depthFrame.height();
      uint32_t frameIndex = depthFrame.frame_index();

      if (width != last_width || height != last_height) {
        buffer_ = buffer_ptr(new int16_t[depthFrame.length()]);
        last_height = height;
        last_width = width;
      }

      depthFrame.copy_to(buffer_.get());
      size_t index = ((width * (height / 2.0f)) + (width / 2.0f));
      short middle = buffer_[index];

      float worldX, worldY, worldZ;
      float depthX, depthY, depthZ;

      mapper.convert_depth_to_world(width / 2.0f, height / 2.0f, middle, worldX,
                                    worldY, worldZ);
      mapper.convert_world_to_depth(worldX, worldY, worldZ, depthX, depthY,
                                    depthZ);
      int w[3] = {(int)worldX, (int)worldY, (int)worldZ};
      int d[3] = {(int)depthX, (int)depthY, (int)depthZ};

      printf("FI[%d],V[%d],W[%d,%d,%d],D[%d,%d,%d]\n", frameIndex, middle, w[0],
             w[1], w[2], d[0], d[1], d[2]);
      fflush(stdout);
      dh->display(buffer_.get());
    }
  }
};

int main(int argc, char *argv[]) {
  astra::initialize();

  DepthHist dh(0, 8000, 128, 480, 640);
  SDL_Event e;

  auto fpsDelay = std::chrono::milliseconds(33);

  astra::StreamSet streamSet;
  astra::StreamReader reader = streamSet.create_reader();

  MyFrameListener listener(&dh);

  auto depthStream = reader.stream<astra::DepthStream>();
  depthStream.start();

  char serialnumber[256];
  depthStream.serial_number(serialnumber, 256);

  printf("DS\n[hFov:[%f],vFov:[%f]]\nSerialNumber:[%s]\n",
         reader.stream<astra::DepthStream>().hFov(),
         reader.stream<astra::DepthStream>().vFov(), serialnumber);
  const uint32_t chipId = depthStream.chip_id();

  switch (chipId) {
  case ASTRA_CHIP_ID_MX400:
    printf("ChipID: MX400\n");
    break;
  case ASTRA_CHIP_ID_MX6000:
    printf("ChipID: MX6000\n");
    break;
  case ASTRA_CHIP_ID_UNKNOWN:
  default:
    printf("ChipID: Unknown\n");
    break;
  }
  const astra_usb_info_t usbinfo = depthStream.usb_info();
  printf("USB info:\n\tPID: [%d]\n\tVID: [%d]\n", usbinfo.pid, usbinfo.vid);

  reader.add_listener(listener);

  while (!dh.quit) {
    auto t1 = std::chrono::high_resolution_clock::now();
    while (SDL_PollEvent(&e)) {
      dh.handle_keys(e);
    }

    dh.draw_coordinates();
    astra_update();
    dh.step();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = t2 - t1;
    if (diff < fpsDelay)
      std::this_thread::sleep_until(t1 + fpsDelay);
    printf("              \r");
    printf("%ld/%ldms",
           std::chrono::duration_cast<std::chrono::milliseconds>(diff).count(),
           std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() - t1)
               .count());
    fflush(stdout);
  }

  reader.remove_listener(listener);
  astra::terminate();

  return 0;
}