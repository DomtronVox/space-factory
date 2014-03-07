#include "model.h"
#include <cassert>

void unitTests() {
    Model * motherModel = new Model;
    string selectedSavedGame;
    assert(motherModel->load(selectedSavedGame)->getMap()->getId() == 0);
}
