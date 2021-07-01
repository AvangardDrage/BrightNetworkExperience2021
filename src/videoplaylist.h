#pragma once

#include <vector>
#include <string>
#include <algorithm>

/** A class used to represent a Playlist */

class VideoPlaylist {
  private:
  public:
    std::string playlistName;
    std::vector<std::string> playlistVideoIdVec;

    VideoPlaylist(std::string iVideoPlaylistName);

    std::string GetPlaylistName();
    const VideoPlaylist *getPlaylist(const std::string& playlistTitle) const;

};
