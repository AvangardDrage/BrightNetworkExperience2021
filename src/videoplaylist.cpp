#include "videoplaylist.h"

VideoPlaylist::VideoPlaylist(std::string iVideoPlaylistName){
  playlistName = iVideoPlaylistName;
}

std::string VideoPlaylist::GetPlaylistName(){
  std::string returnName = playlistName;
  std::transform(returnName.begin(), returnName.end(), returnName.begin(),
  [](unsigned char c){ return std::tolower(c);});
  return returnName;
}
