#include "View.h"

View::View() : error(false) {}

View::~View() = default;

void View::setError(bool _error) {
    View::error = _error;
}