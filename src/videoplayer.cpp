#include "videoplayer.h"

#include <iostream>

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

void VideoPlayer::showAllVideos() {
  std::vector<std::string> videoTitleVec;
  std::string videoTitle;

  std::cout << "Here's a list of all available videos: " << std::endl;

  for (auto &video: mVideoLibrary.getVideos()){
    videoTitleVec.push_back(video.getVideoInfo());
  }

  std::sort(videoTitleVec.begin(), videoTitleVec.end());

  for (auto &title : videoTitleVec){
    std::cout << "    " << title;
    std::cout << std::endl;
  }
}

void VideoPlayer::playVideo(const std::string& videoId) {
  auto videoPlaying = mVideoLibrary.getVideo(videoId);

  if (videoPlaying!=nullptr){
    if (isVideoPlayingFlag) {
      std::cout<< "Stopping video: " + titleVideoPlaying << std::endl;
    }
    titleVideoPlaying = videoPlaying->getTitle();
    idVideoPlaying = videoPlaying->getVideoId();
    tagsVideoPlaying = videoPlaying->getTags();

    std::cout<< "Playing video: " + titleVideoPlaying << std::endl;
    isVideoPlayingFlag = true;
    isVideoPausedFlag = false;
  }
  else {
      std::cout << "Cannot play video: Video does not exist" << std::endl;
    }
}

void VideoPlayer::stopVideo() {
  if (isVideoPlayingFlag) {
    std::cout << "Stopping video: " + titleVideoPlaying << std::endl;
    isVideoPlayingFlag = false;
  }
  else{
    std::cout << "Cannot stop video: No video is currently playing" << std::endl;
  }
}

void VideoPlayer::playRandomVideo() {
  if (isVideoPlayingFlag){
    std::cout << "Stopping video: " + titleVideoPlaying << std::endl;
    isVideoPlayingFlag = false;
  }

  srand(time(NULL));
  int itrKey = rand() % mVideoLibrary.getVideos().size();

  auto videoPlaying = mVideoLibrary.getVideos()[itrKey];

  titleVideoPlaying = videoPlaying.getTitle();
  idVideoPlaying = videoPlaying.getVideoId();
  tagsVideoPlaying = videoPlaying.getTags();

  std::cout << "Playing video: " + titleVideoPlaying << std::endl;
  isVideoPlayingFlag = true;
  isVideoPausedFlag = false;
}

void VideoPlayer::pauseVideo() {
  if (isVideoPlayingFlag){
    if (isVideoPausedFlag) {
      std::cout << "Video already paused: " + titleVideoPlaying << std::endl;
    }
    else {
      std::cout << "Pausing video: " + titleVideoPlaying << std::endl;
      isVideoPausedFlag = true;
    }
  }
  else{
    std::cout << "Cannot pause video: No video is currently playing" << std::endl;
  }
}

void VideoPlayer::continueVideo() {
  if (isVideoPlayingFlag) {
    if (isVideoPausedFlag){
      std::cout << "Continuing video: " + titleVideoPlaying << std::endl;
      isVideoPausedFlag = false;
    }
    else
    {
      std::cout << "Cannot continue video: Video is not paused" << std::endl;
    }
  }
  else {
    std::cout << "Cannot continue video: No video is currently playing" << std::endl;
  }
}

void VideoPlayer::showPlaying() {
  if (isVideoPlayingFlag) {
    std::string showInfo;
    showInfo+= titleVideoPlaying;
    showInfo+= " ";
    showInfo+= "(";
    showInfo+= idVideoPlaying;
    showInfo+= ")";
    showInfo+= " ";
    showInfo+= "[";
    bool spaceFlag=false;
    for (auto &tag: tagsVideoPlaying){
      if(spaceFlag) {
        showInfo+=" ";
      }
      showInfo+=tag;
      spaceFlag=true;
    }
    showInfo+= "]";
    if (isVideoPausedFlag){
      showInfo+= " - PAUSED";
    }
    std::cout << "Currently playing: " << showInfo << std::endl;
  }
  else{
    std::cout << "No video is currently playing" << std::endl;
  }
}

void VideoPlayer::createPlaylist(const std::string& iPlaylistName) {

  bool isPlaylistNewFlag = true;
  std::string inputTitle = iPlaylistName;

  std::transform(inputTitle.begin(), inputTitle.end(), inputTitle.begin(),
  [](unsigned char c){ return std::tolower(c);});

  for (auto entry : videoPlaylistMap){
    std::string entryTitle = entry.first;

    std::transform(entryTitle.begin(), entryTitle.end(), entryTitle.begin(),
                   [](unsigned char c){ return std::tolower(c);});

    if (entryTitle == inputTitle){
      isPlaylistNewFlag = false;
    }
  }

  if (isPlaylistNewFlag){
    VideoPlaylist playlist(iPlaylistName);
    videoPlaylistMap.emplace(inputTitle, playlist);
    std::cout << "Successfully created new playlist: " << iPlaylistName << std::endl;
  }
  else {
    std::cout<<"Cannot create playlist: A playlist with the same name already exists"<<std::endl;
  }
}

void VideoPlayer::addVideoToPlaylist(const std::string& iPlaylistName,
                                     const std::string& iVideoId)
                                      {

  bool doesPlaylistExistsFlag = false;
  bool isVideoInPlaylistFlag = false;

  std::string inputTitle = iPlaylistName;

  std::transform(inputTitle.begin(), inputTitle.end(), inputTitle.begin(),
  [](unsigned char c){ return std::tolower(c);});

  for (auto entry : videoPlaylistMap){

    if (entry.first == inputTitle){
      doesPlaylistExistsFlag = true;
    }

    if (entry.second.playlistVideoIdMap.find(iVideoId)!=entry.second.playlistVideoIdMap.end()){
        isVideoInPlaylistFlag = true;
    }
  }


  if (!doesPlaylistExistsFlag) {
    std::cout << "Cannot add video to "<< iPlaylistName << ": Playlist does not exist" << std::endl;
  }
  else {
    auto videoPlaying = mVideoLibrary.getVideo(iVideoId);
    if (videoPlaying == nullptr){
      std::cout << "Cannot add video to "<< iPlaylistName << ": Video does not exist";
    }
    else{
      if (isVideoInPlaylistFlag) {
        std::cout << "Cannot add video to " << iPlaylistName<<": Video already added" << std::endl;
      }
      else{
        const auto playlistInMap = videoPlaylistMap.find(inputTitle);
        (playlistInMap->second).playlistVideoIdMap.emplace(iVideoId,iVideoId);
        std::cout << "Added video to " << iPlaylistName << ": " << mVideoLibrary.getVideo(iVideoId)->getTitle() << std::endl;
      }
    }
  }

}

void VideoPlayer::showAllPlaylists() {
  if (videoPlaylistMap.empty()) {
    std::cout << "No playlists exist yet" << std::endl;
  }
  else{
    std::cout << "Showing all playlists:" << std::endl;
    for (auto playlist : videoPlaylistMap){
      std::cout << "    " << playlist.second.playlistName << std::endl;
    }
  }
}

void VideoPlayer::showPlaylist(const std::string& iPlaylistName) {
  std::string inputTitle = iPlaylistName;

  std::transform(inputTitle.begin(), inputTitle.end(), inputTitle.begin(),
  [](unsigned char c){ return std::tolower(c);});

  if (videoPlaylistMap.find(inputTitle) == videoPlaylistMap.end()){
    std::cout << "Cannot show playlist " << iPlaylistName << ": Playlist does not exist" << std::endl;
  }
  else {
    auto videoPlaylist = videoPlaylistMap.find(inputTitle)->second;
    std::cout << "Showing playlist: " << iPlaylistName << std::endl;
    if (videoPlaylist.playlistVideoIdMap.empty()){
      std::cout << "    No videos here yet" << std::endl;
    }
    else{
      for (auto videoId : videoPlaylist.playlistVideoIdMap)
      std::cout << "    " << mVideoLibrary.getVideo(videoId.second)->getVideoInfo() << std::endl;
    }
  }
}

void VideoPlayer::removeFromPlaylist(const std::string& iPlaylistName,
                                     const std::string& iVideoId)
{
  std::string inputTitle = iPlaylistName;

  std::transform(inputTitle.begin(), inputTitle.end(), inputTitle.begin(),
  [](unsigned char c){ return std::tolower(c);});

  if (videoPlaylistMap.find(inputTitle) == videoPlaylistMap.end()){
    std::cout << "Cannot remove video from " << iPlaylistName << ": Playlist does not exist" << std::endl;
  }
  else{
    if (mVideoLibrary.getVideo(iVideoId)==nullptr){
      std::cout << "Cannot remove video from " <<  iPlaylistName <<": Video does not exist" << std::endl;
    }
    else{
      //auto videoPlaylist = videoPlaylistMap.find(inputTitle);
      if (videoPlaylistMap.at(inputTitle).playlistVideoIdMap.find(iVideoId) == videoPlaylistMap.at(inputTitle).playlistVideoIdMap.end()){
        std::cout << "Cannot remove video from "<< iPlaylistName <<": Video is not in playlist" << std::endl;
      }
      else {
        videoPlaylistMap.at(inputTitle).playlistVideoIdMap.erase(iVideoId);
        std::cout << "Removed video from " << iPlaylistName <<": "<< mVideoLibrary.getVideo(iVideoId)->getTitle() << std::endl;
      }
    }
  }
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  std::cout << "deletePlaylist needs implementation" << std::endl;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::cout << "searchVideos needs implementation" << std::endl;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
