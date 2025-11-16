#include "../../include/entities/Grade.h"

void Grade::calculateTotal() {
    total = chinese + math + english + history + geography + biology + physics + politics;
}