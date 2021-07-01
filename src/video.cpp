#include "video.h"

#include <iostream>
#include <utility>
#include <vector>

Video::Video(std::string&& title, std::string&& videoId,
             std::vector<std::string>&& tags) :
  mTitle(std::move(title)),
  mVideoId(std::move(videoId)),
  mTags(std::move(tags)) {
}

const std::string& Video::getTitle() const { return mTitle; }

const std::string& Video::getVideoId() const { return mVideoId; }

const std::vector<std::string>& Video::getTags() const { return mTags; }

const std::string Video::getVideoInfo() const {
  std::string videoInfo;
  videoInfo += mTitle;
  videoInfo += " ";
  videoInfo += "(";
  videoInfo += mVideoId;
  videoInfo += ")";
  videoInfo += " ";
  videoInfo += "[";
  bool spaceFlag = false;
  for (auto &tag: mTags){
    if(spaceFlag) {
      videoInfo+=" ";
    }
    videoInfo+=tag;
    spaceFlag=true;
  }
  videoInfo+="]";
  return videoInfo;
}
