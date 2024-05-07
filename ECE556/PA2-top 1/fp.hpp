#pragma once

#include <vector>
#include <variant>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <climits>
#include <random>
#include <set>


namespace fp {


struct Block {
  std::string name;

  unsigned left_x = 0;
  unsigned left_y = 0;
  unsigned saved_left_x = 0;
  unsigned saved_left_y = 0;
  unsigned width = 0;
  unsigned height = 0;
  unsigned saved_width = 0;
  unsigned saved_height = 0;
 
  std::vector<Block*> rights;
  std::vector<Block*> aboves;
  std::vector<Block*> saved_rights;
  std::vector<Block*> saved_aboves;
 
  int idx_pseqs = -1;
  int idx_nseqs = -1;
  int saved_idx_pseqs = -1;
  int saved_idx_nseqs = -1;
};

struct Terminal {
  size_t pos_x = 0;
  size_t pos_y = 0;
  std::string name;
};

struct Net {
  std::vector<std::variant<Block*, Terminal*>> net;
};


class FP {

  public:

    float alpha = 0;
    const float init_T = 1000.0;
    const float frozen_T = 0.5;
    const float decay = 0.95;
    const size_t iter_per_temp = 1000;
    int penalty_ratio = 2;
  
    FP (float alpha, const std::string& input_block_path, const std::string& input_net_path, const std::string& out_path) 
      : _gen(_rd()) , alpha(alpha) , _output_path(out_path) {
      _read_input(input_block_path, input_net_path);
    }

    void run() { _fp(); };
    void dump() { _write(); };

    ~FP() = default;

  private:

    std::string _output_path; 

    std::random_device _rd;
    std::mt19937 _gen;
    std::uniform_int_distribution<size_t> _dist;

    std::unordered_map<std::string, Block> _blocks;
    std::unordered_map<std::string, Terminal> _terminals;
    std::vector<Net> _nets;
    std::vector<Block*> _pseqs;
    std::vector<Block*> _nseqs;
    std::vector<Block*> _saved_pseqs;
    std::vector<Block*> _saved_nseqs;
    std::vector<int> _distance;
    std::vector<bool> _in_queue;
    std::deque<Block*> _queue;
    std::set<Block*> _affected;
    std::vector<Block*> _vec;  

    size_t _outline_w;
    size_t _outline_h;
    size_t _num_blocks;
    size_t _num_terminals;
    size_t _num_nets;

    Block _source;
    Block _terminus;

    int _bbox_w = 0;
    int _bbox_h = 0;
    int _hpwl = 0;
    int _saved_bbox_w = 0;
    int _saved_bbox_h = 0;
    int _saved_hpwl = 0;

    float _avg_area = 0.0;
    float _avg_len = 0.0;
    size_t _num_itr = 0;
    int _over_len = 0;

    void _read_input(const std::string& input_block_path, const std::string& input_net_path);
    void _fp();
    float _pack();
    void _shortest_path(int vertical);
    void _build_locations(const size_t id1, const size_t id2, int move);
    void _update_saved(const size_t id1, const size_t id2, int move);
    void _restore_saved(const size_t id1, const size_t id2, int move);
    void _write();

};


void FP::_read_input(const std::string& input_block_path, const std::string& input_net_path) {


  _source.name = "source";
  _terminus.name = "terminus";

  std::ifstream inBlkFile(input_block_path, std::ios::in);
  if (!inBlkFile) {
    std::cerr << "File does not exist!\n";
    exit(1);
  }

  std::ifstream inNetFile(input_net_path, std::ios::in);
  if (!inNetFile) {
    std::cerr << "File does not exist!\n";
    exit(1);
  }

  std::string line;
  std::regex reg("\\s+");
 
  // outline of width and height
  std::getline(inBlkFile, line);
  std::sregex_token_iterator it(line.begin(), line.end(), reg, -1);
  _outline_w  = std::stoi(*(++it)); 
  _outline_h = std::stoi(*(++it)); 

  // number of blocks
  std::getline(inBlkFile, line);
  it = std::sregex_token_iterator(line.begin(), line.end(), reg, -1);
  _num_blocks = std::stoi(*(++it)); 
  
  // number of terminals
  std::getline(inBlkFile, line);
  it = std::sregex_token_iterator(line.begin(), line.end(), reg, -1);
  _num_terminals = std::stoi(*(++it)); 

  size_t num_lines = 0;
  while (std::getline(inBlkFile, line)) {
    
    if (line[0] < 'A' || (line[0] > 'Z' && line[0] < 'a') || line[0] > 'z') {
      continue; 
    }
    
    it = std::sregex_token_iterator(line.begin(), line.end(), reg, -1);
    
    // dimensions of blocks
    if (num_lines < _num_blocks) {
      Block blk;
      blk.name = *(it);
      blk.width = std::stoi(*(++it));
      blk.height = std::stoi(*(++it));
      _blocks[blk.name] = blk;
      ++num_lines;
    }

    // settings of terminals
    else {
      Terminal t;
      t.name = *(it);
      ++it;
      t.pos_x = std::stoi(*(++it));
      t.pos_y = std::stoi(*(++it));
      _terminals[t.name] = t;
    }
  }

  
  // number of nets 
  std::getline(inNetFile, line);
  it = std::sregex_token_iterator(line.begin(), line.end(), reg, -1);
  _num_nets  = std::stoi(*(++it)); 

  // configurations of nets
  while (std::getline(inNetFile, line)) {
    if (line.size() == 0) {
      continue;
    }
    
    size_t netdegree = 0;
    it = std::sregex_token_iterator(line.begin(), line.end(), reg, -1);
    netdegree = std::stoi(*(++it));
    
    Net n;
    for (size_t i = 0; i < netdegree; ++i) {
      std::variant<Block*, Terminal*> var;
      std::getline(inNetFile, line);
      it = std::sregex_token_iterator(line.begin(), line.end(), reg, -1);
      
      if (_blocks.find(*it) != _blocks.end()) {
        var = &(_blocks[*it]);
      }
      else {
        var = &(_terminals[*it]);
      }
      n.net.emplace_back(var);
    }
    _nets.emplace_back(n);
  }
  
  _pseqs.resize(_num_blocks);
  _nseqs.resize(_num_blocks);
  size_t idx = _dist(_gen)%_num_blocks;
  for (auto& [key, value] : _blocks) {
    while (_pseqs[idx] != nullptr) {
      idx = _dist(_gen)%_num_blocks;
    }
    _pseqs[idx] = &(_blocks[key]);
    _blocks[key].idx_pseqs = idx;
    idx = _dist(_gen)%_num_blocks; 
    while (_nseqs[idx] != nullptr) {
      idx = _dist(_gen)%_num_blocks;
    }
    _nseqs[idx] = &(_blocks[key]);
    _blocks[key].idx_nseqs = idx;
  }
}


void FP::_build_locations(const size_t id1, const size_t id2, int move) {

  _affected.clear();

  switch(move) {  
    case 0:
    case 1:
      for (size_t i = id1; i <= id2; ++i) {
        _affected.insert(_pseqs[i]);
      }
      break;

    case 2:
      for (size_t i = id1; i <= id2; ++i) {
        _affected.insert(_nseqs[i]);
      }
      break;
    
    case 3:
      size_t nid1, nid2;
      nid1 = _pseqs[id1]->idx_nseqs;
      nid2 = _pseqs[id2]->idx_nseqs;
      for (size_t i = id1; i <= id2; ++i) {
        _affected.insert(_pseqs[i]);
      }
      if (nid1 > nid2) {
        std::swap(nid1, nid2);
      }
      for (size_t i = nid1; i <= nid2; ++i) {
        _affected.insert(_nseqs[i]);
      }
      break;
    
    case 4:
      break;
  }

  int pidx, nidx;
  for (auto& blk : _affected) {
    blk->rights.clear();
    pidx = blk->idx_pseqs+1;
    nidx = blk->idx_nseqs;
    while (pidx < _num_blocks) {
      Block* target = _pseqs[pidx];
      if (target->idx_nseqs > nidx) {
        blk->rights.push_back(target);
      }
      ++pidx;
    }
    if (move != 0) {  
      blk->rights.push_back(&_terminus);
    }
  }

  for (auto& blk : _affected) {
    blk->aboves.clear();
    pidx = static_cast<int>(blk->idx_pseqs)-1; 
    nidx = blk->idx_nseqs;
    while (pidx >= 0) {
      Block* target = _pseqs[pidx];
      if (target->idx_nseqs > nidx) {
        blk->aboves.push_back(target);
      }
      --pidx;
    }
    if (move != 0) {  
      blk->aboves.push_back(&_terminus);
    }
  }
  
  if (move != 0) {
    return; 
  }

  for (auto& [key, value] : _blocks) {
    _source.rights.push_back(&value);
    _source.aboves.push_back(&value);
    value.rights.push_back(&_terminus);
    value.aboves.push_back(&_terminus);
  }
}


void FP::_shortest_path(int vertical) {  
  _queue.clear();
  _distance.clear();
  _in_queue.clear();
  _distance.resize(_num_blocks+2, INT_MAX);  
  _in_queue.resize(_num_blocks+2, false);

  _distance[0] = 0;
  _queue.push_back(&_source);
  _in_queue[0] = true;

  while (!_queue.empty()) {
    Block* u = _queue.front();
    _queue.pop_front();

    size_t indexu = 0, indexv = 0;
    if (u->idx_pseqs == -1) {
      if (u == &_source) {
        indexu = 0;
      }
      else {
        indexu = _num_blocks+1;
      }
    }
    else {
      indexu = u->idx_pseqs+1;
    }
    _in_queue[indexu] = false;
  
    if (vertical) {  
      _vec = u->aboves;
    }
    else {
      _vec = u->rights;
    }
    for (auto& blk : _vec) {

      if (blk->idx_pseqs == -1) {
        if (blk == &_source) {
          indexv = 0;
        }
        else {
          indexv = _num_blocks+1;
        }
      }
      else {
        indexv = blk->idx_pseqs+1;
      }
     
      int weight = 0;
      if (vertical) {  
        weight = -1 * static_cast<int>(blk->height);
      }
      else {
        weight = -1 * static_cast<int>(blk->width);
      }
      
      if (_distance[indexu] + weight < _distance[indexv]) {
        _distance[indexv] = _distance[indexu] + weight;
        if (_in_queue[indexv] == false) {
          _queue.push_back(blk);
          _in_queue[indexv] = true;
        }
      }
    }
  }
}


void FP::_update_saved(const size_t id1, const size_t id2, int move) {

  size_t nid1, nid2;
  switch(move) {  
    case 1:
      std::swap(_saved_pseqs[id1], _saved_pseqs[id2]);
      _pseqs[id1]->saved_idx_pseqs = id1;
      _pseqs[id2]->saved_idx_pseqs = id2;
      for (size_t i = id1; i <= id2; ++i) {
        _pseqs[i]->saved_rights = _pseqs[i]->rights;
        _pseqs[i]->saved_aboves =  _pseqs[i]->aboves;
      }
      for (auto& [key, value] : _blocks) {
        value.saved_left_x = value.left_x;
        value.saved_left_y = value.left_y;
      }
      break;
    
    case 2:
      std::swap(_saved_nseqs[id1], _saved_nseqs[id2]);
      _nseqs[id1]->saved_idx_nseqs = id1;
      _nseqs[id2]->saved_idx_nseqs = id2;
      for (size_t i = id1; i <= id2; ++i) {
        _nseqs[i]->saved_rights = _nseqs[i]->rights;
        _nseqs[i]->saved_aboves = _nseqs[i]->aboves;
      }
      for (auto& [key, value] : _blocks) {
        value.saved_left_x = value.left_x;
        value.saved_left_y = value.left_y;
      }
      break;

    case 3:
      std::swap(_saved_pseqs[id1], _saved_pseqs[id2]);
      _pseqs[id1]->saved_idx_pseqs = id1;
      _pseqs[id2]->saved_idx_pseqs = id2;
      for (size_t i = id1; i <= id2; ++i) {
        _pseqs[i]->saved_rights = _pseqs[i]->rights;
        _pseqs[i]->saved_aboves = _pseqs[i]->aboves;
      }
      nid1 = _pseqs[id1]->idx_nseqs;
      nid2 = _pseqs[id2]->idx_nseqs;
      std::swap(_saved_nseqs[nid1], _saved_nseqs[nid2]);
      _nseqs[nid1]->saved_idx_nseqs = nid1;
      _nseqs[nid2]->saved_idx_nseqs = nid2;
      if (nid1 > nid2) {
        std::swap(nid1, nid2);
      }
      for (size_t i = nid1; i <= nid2; ++i) {
        _nseqs[i]->saved_rights = _nseqs[i]->rights;
        _nseqs[i]->saved_aboves = _nseqs[i]->aboves;
      }
      for (auto& [key, value] : _blocks) {
        value.saved_left_x = value.left_x;
        value.saved_left_y = value.left_y;
      }
      break;
    
    case 4:
      _pseqs[id1]->saved_width = _pseqs[id1]->width; 
      _pseqs[id1]->saved_height = _pseqs[id1]->height; 
      for (auto& [key, value] : _blocks) {
        value.saved_left_x = value.left_x;
        value.saved_left_y = value.left_y;
      }
      break;
    
    case 0:
      std::cerr << "move error!\n";
      exit(-1);
    break;
  }
  _saved_bbox_w  = _bbox_w;
  _saved_bbox_h = _bbox_h;
  _saved_hpwl = _hpwl;
}


void FP::_restore_saved(const size_t id1, const size_t id2, int move) {

  size_t nid1, nid2;
  switch(move) {  
    case 1:
      std::swap(_pseqs[id1], _pseqs[id2]);
      _pseqs[id1]->idx_pseqs = _pseqs[id1]->saved_idx_pseqs;
      _pseqs[id2]->idx_pseqs = _pseqs[id2]->saved_idx_pseqs;
      for (size_t i = id1; i <= id2; ++i) {
        _pseqs[i]->rights = _pseqs[i]->saved_rights;
        _pseqs[i]->aboves = _pseqs[i]->saved_aboves;
      }
      for (auto& [key, value] : _blocks) {
        value.left_x = value.saved_left_x;
        value.left_y = value.saved_left_y;
      }
      break;
    
    case 2:
      std::swap(_nseqs[id1], _nseqs[id2]);
      _nseqs[id1]->idx_nseqs = _nseqs[id1]->saved_idx_nseqs; 
      _nseqs[id2]->idx_nseqs = _nseqs[id2]->saved_idx_nseqs; 
      for (size_t i = id1; i <= id2; ++i) {
        _nseqs[i]->rights = _nseqs[i]->saved_rights;
        _nseqs[i]->aboves = _nseqs[i]->saved_aboves;
      }
      for (auto& [key, value] : _blocks) {
        value.left_x = value.saved_left_x;
        value.left_y = value.saved_left_y;
      }
      break;

    case 3:
      std::swap(_pseqs[id1], _pseqs[id2]);
      _pseqs[id1]->idx_pseqs = _pseqs[id1]->saved_idx_pseqs;
      _pseqs[id2]->idx_pseqs = _pseqs[id2]->saved_idx_pseqs;
      for (size_t i = id1; i <= id2; ++i) {
        _pseqs[i]->rights = _pseqs[i]->saved_rights;
        _pseqs[i]->aboves = _pseqs[i]->saved_aboves;
      }
      nid1 = _pseqs[id1]->idx_nseqs;
      nid2 = _pseqs[id2]->idx_nseqs;
      std::swap(_nseqs[nid1], _nseqs[nid2]);
      _nseqs[nid1]->idx_nseqs = _nseqs[nid1]->saved_idx_nseqs;
      _nseqs[nid2]->idx_nseqs = _nseqs[nid2]->saved_idx_nseqs;
      if (nid1 > nid2) {
        std::swap(nid1, nid2);
      }
      for (size_t i = nid1; i <= nid2; ++i) {
        _nseqs[i]->rights = _nseqs[i]->saved_rights;
        _nseqs[i]->aboves = _nseqs[i]->saved_aboves;
      }
      for (auto& [key, value] : _blocks) {
        value.left_x = value.saved_left_x;
        value.left_y = value.saved_left_y;
      }
      break;

    case 4:
      _pseqs[id1]->width = _pseqs[id1]->saved_width;
      _pseqs[id1]->height = _pseqs[id1]->saved_height;
      for (auto& [key, value] : _blocks) {
        value.left_x = value.saved_left_x;
        value.left_y = value.saved_left_y;
      }
      break;

    case 0:
      std::cerr << "move error!\n";
      exit(-1);
      break;
  }
  _bbox_w  = _saved_bbox_w;
  _bbox_h = _saved_bbox_h;
  _hpwl = _saved_hpwl;
}


float FP::_pack() {
  _over_len = 0;
  _shortest_path(0);
  for (auto& [key, value] : _blocks) {
    value.left_x = -1*_distance[value.idx_pseqs+1] - value.width;
  }
  _bbox_w = INT_MIN;
  for (auto& [key, value] : _blocks) {
    if (_bbox_w <= -1*_distance[value.idx_pseqs+1])
      _bbox_w = -1*_distance[value.idx_pseqs+1];
    int len = -1*_distance[value.idx_pseqs+1]-static_cast<int>(_outline_w);
    if (len > 0) {
      _over_len = _over_len + penalty_ratio*len;
    }
  }

  _shortest_path(1);
  for (auto& [key, value] : _blocks) {
    value.left_y = -1*_distance[value.idx_pseqs+1] - value.height;
  }
  _bbox_h = INT_MIN;
  for (auto& [key, value] : _blocks) {
    if (_bbox_h <= -1*_distance[value.idx_pseqs+1])
      _bbox_h = -1*_distance[value.idx_pseqs+1];
    int len = -1*_distance[value.idx_pseqs+1]-static_cast<int>(_outline_h);
    if (len > 0) {
      _over_len = _over_len + penalty_ratio*len;
    }
  }

  _hpwl = 0;
  int max_x = 0, min_x = INT_MAX, max_y = 0, min_y = INT_MAX;
  int llx = 0, lly = 0;
 
  for (auto& net : _nets) {
 
    max_x = 0;
    min_x = INT_MAX;
    max_y = 0;
    min_y = INT_MAX;
    llx = 0;
    lly = 0;
 
    for (const auto& n : net.net) {
      if (std::holds_alternative<Terminal*>(n)) {
        llx = 2*std::get<Terminal*>(n)->pos_x;
        lly = 2*std::get<Terminal*>(n)->pos_y;
      }
      else {
        int x = std::get<Block*>(n)->left_x;
        int y = std::get<Block*>(n)->left_y;
        int w = std::get<Block*>(n)->width;
        int h = std::get<Block*>(n)->height;
        llx = 2*x + ((x+w)-x);
        lly = 2*y + ((y+h)-y);
      }
      if (llx >= max_x) {
        max_x = llx;
      }
      if (llx <= min_x) {
        min_x = llx;
      }
      if (lly >= max_y) {
        max_y = lly;
      }
      if (lly <= min_y) {
        min_y = lly;
      }
    }
 
    _hpwl += (max_x-min_x) + (max_y-min_y);
  }
  _hpwl /= 2;
  _avg_area = (_avg_area*(_num_itr-1) + _bbox_w*_bbox_h)/static_cast<float>(_num_itr);
  _avg_len = (_avg_len*(_num_itr-1) + _hpwl)/static_cast<float>(_num_itr); 
  return (alpha*_bbox_w*_bbox_h/_avg_area)+(1-alpha)*(_hpwl+_over_len)/_avg_len;
}


void FP::_fp() {
  bool pass = false;
  float curr_T = init_T;
  
  // first run
  ++_num_itr;
  _build_locations(0, _num_blocks-1, 0);
  float backup_cost = _pack();
  float cost = backup_cost;
 
  // backup data  
  for (auto& [key, value] : _blocks) {
    value.saved_width = value.width;
    value.saved_height = value.height;
    value.saved_left_x = value.left_x;
    value.saved_left_y = value.left_y;
    value.saved_rights = value.rights;
    value.saved_aboves = value.aboves;
    value.saved_idx_pseqs = value.idx_pseqs;
    value.saved_idx_nseqs = value.idx_nseqs;
  }

  _saved_bbox_w = _bbox_w;
  _saved_bbox_h = _bbox_h;
  _saved_hpwl = _hpwl;
  _saved_pseqs = _pseqs;
  _saved_nseqs = _nseqs;

  // SA 
  float delta = 0.0;
  size_t rv;
  std::pair<size_t, size_t> pair_idx;
  int move;

  do { 
    size_t id, id1, id2, nid1, nid2;
    while (curr_T > frozen_T) {
      for (size_t ite = 0; ite < iter_per_temp; ++ite) {

        rv = _dist(_gen)%4;
        switch (rv) {
          case 0:
            id1 = _dist(_gen)%_num_blocks;
            id2 = _dist(_gen)%_num_blocks;
            while (id1 == id2) {
              id2 =_dist(_gen)%_num_blocks;
            }
            if (id1 > id2) {
              std::swap(id1, id2);
            }
            std::swap(_pseqs[id1], _pseqs[id2]);
            _pseqs[id1]->idx_pseqs = id1;
            _pseqs[id2]->idx_pseqs = id2;
            pair_idx = std::make_pair(id1, id2);
            move = 1;
            break;

          // a new neighbor from move2 
          case 1:
            id1 = _dist(_gen)%_num_blocks;
            id2 = _dist(_gen)%_num_blocks;
            while (id1 == id2) {
              id2 = _dist(_gen)%_num_blocks;
            }
            if (id1 > id2) {
              std::swap(id1, id2);
            }
            std::swap(_nseqs[id1], _nseqs[id2]);
            _nseqs[id1]->idx_nseqs = id1;
            _nseqs[id2]->idx_nseqs = id2;
            pair_idx = std::make_pair(id1, id2);
            move = 2;
            break;
          // a new neighbor from move3
          case 2:
            id1 = _dist(_gen)%_num_blocks;
            id2 = _dist(_gen)%_num_blocks;
            while (id1 == id2) {
              id2 = _dist(_gen)%_num_blocks;
            }
            if (id1 > id2) {
              std::swap(id1, id2);
            }
            std::swap(_pseqs[id1], _pseqs[id2]);
            _pseqs[id1]->idx_pseqs = id1;
            _pseqs[id2]->idx_pseqs = id2;
            nid1 = _pseqs[id1]->idx_nseqs;
            nid2 = _pseqs[id2]->idx_nseqs;
            std::swap(_nseqs[nid1], _nseqs[nid2]);
            _nseqs[nid1]->idx_nseqs = nid1;
            _nseqs[nid2]->idx_nseqs = nid2;
            pair_idx = std::make_pair(id1, id2); 
            move = 3;
            break;

          // a new neighbor from move4
          case 3:
            id = _dist(_gen)%_num_blocks;
            while (_pseqs[id]->width == _pseqs[id]->height) {
              id = _dist(_gen)%_num_blocks;
            }
            std::swap(_pseqs[id]->width, _pseqs[id]->height);
            pair_idx = std::make_pair(id, id);
            move = 4;
            break;
        }

        _build_locations(pair_idx.first, pair_idx.second, move);
        ++_num_itr;
        cost = _pack(); 
        delta = (cost - backup_cost) * 1000;
        
        // better neighbor, always accept it
        if (delta < 0) {
          _update_saved(pair_idx.first, pair_idx.second, move);
          backup_cost = cost;
        }

        // worse neighbor
        else {
          auto prob = std::exp(-delta/curr_T);

          // accept the worse neighbor
          if (prob > static_cast<float>(_dist(_gen))/_dist.max()) {   
            _update_saved(pair_idx.first, pair_idx.second, move);
            backup_cost = cost;
          }

          // decline the worse neighbor
          else {
            _avg_area = (_avg_area*_num_itr-_bbox_w*_bbox_h)/(_num_itr-1);
            _avg_len = (_avg_len*_num_itr-_hpwl)/(_num_itr-1);
            --_num_itr;

            _restore_saved(pair_idx.first, pair_idx.second, move);
          }
        }
      }

      curr_T *= decay;
    }

    if (_outline_w >= _outline_h) {
      if (_bbox_w >= _bbox_h) {
        if (_outline_w >= _bbox_w && _outline_h >= _bbox_h) {
          pass = true; 
        }
      }
      else {
        if (_outline_w >= _bbox_h && _outline_h >= _bbox_w) {
          pass = true;
        }
      }
    }

    else {
      if (_bbox_w >= _bbox_h) {
        if (_outline_w >= _bbox_h && _outline_h >= _bbox_w) {
          pass = true;
        }
      }
      else {
        if (_outline_w >= _bbox_w && _outline_h >= _bbox_h) {
          pass = true;
        }
      }
    }
    if (pass == false) {
      curr_T = init_T;
      penalty_ratio *= 2;
    }
  }
  while(pass == false);

}


void FP::_write() {
  std::ofstream outFile(_output_path, std::ios::out);

  if (!outFile) {
    std::cerr << "Output file does not exist!\n";
    exit(1);
  }

  outFile << (_hpwl + _bbox_w*_bbox_h) << '\n';
  outFile << _hpwl << '\n';
  outFile << _bbox_w * _bbox_h << '\n';
  outFile << _bbox_w << ' ' << _bbox_h << '\n';
  outFile << 10 << '\n';
  
  if ( ((_outline_w >= _outline_h) && (_bbox_w >= _bbox_h)) ||
       ((_outline_w <= _outline_h) && (_bbox_w <= _bbox_h)) ) {
    for (auto& [key, value] : _blocks) {
      outFile << key << ' '
              << value.left_x << ' '
              << value.left_y << ' '
              << value.left_x + value.width  << ' '
              << value.left_y + value.height << '\n';   
    }
  }
 
  else { 
    for (auto& [key, value] : _blocks) {
      outFile << key << ' '
              << value.left_y << ' '
              << value.left_x << ' '
              << value.left_y + value.height << ' '
              << value.left_x + value.width  << '\n';   
    }
  }
}

} // end of namespace fp
