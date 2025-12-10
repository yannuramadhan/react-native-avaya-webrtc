#import "VideoViewManager.h"

@implementation VideoView
@end

@implementation VideoViewManager

RCT_EXPORT_MODULE(VideoView)

- (UIView *)view
{
  // View kosong, nanti Avaya SDK isi remote/local video
  return [[UIView alloc] init];
}

@end
