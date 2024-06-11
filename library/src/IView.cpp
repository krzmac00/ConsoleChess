#include "IView.h"

IView::IView() : error(false) {}

IView::~IView() = default;

void IView::setError(bool _error) {
    IView::error = _error;
}