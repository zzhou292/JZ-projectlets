// Hint for PA1

using namespace pa1;

// =========================
// Definition form the system perspective
// =========================

// cell data struture
struct Cell{
  std::vector<Net*> nets;
  int gain;
  int weight;

  bool partition; // true for P1, false for P2.

  // iterator
  std::list<Cell*>::iterator satellite;
}

// net data structure
struct Net{
  std::vector<Cell*> cells;
}

class FMPartitioner{
  public:

  private:

  std::vector<Net> _nets;
  std::vector<Cell> _cells;
  
  // bucket list
  std::vector<std::list<Cell*>> _bktlist;
}; // end of definition pa1

// ================================
// Def from the application perspective
// ================================

int main(){
  
  pa1::FMPartition partitioner;
  partitioner.read();

}

