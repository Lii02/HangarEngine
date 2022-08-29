#include "precompiled.h"
#include "system_window.h"

bool SystemWindow::get_is_resizable() const {
	return is_resizable;
}

bool SystemWindow::get_is_running() const {
	return is_running;
}

AString SystemWindow::get_title() const {
	return title;
}

void SystemWindow::set_title(AString new_title) {
	title = new_title;
}

void SystemWindow::set_is_resizable(bool _is_resizable) {
	is_resizable = _is_resizable;
}

SystemWindow::Dimensions SystemWindow::get_dimensions() {
	return dimensions;
}

void SystemWindow::set_dimensions(SystemWindow::Dimensions new_dimensions) {
	dimensions = new_dimensions;
}