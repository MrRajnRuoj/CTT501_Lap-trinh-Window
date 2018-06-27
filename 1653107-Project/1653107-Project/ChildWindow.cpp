#include "stdafx.h"
#include "ChildWindow.h"

void ChildWindow::setHandle(HWND hWnd) {
	if (hWnd < 0)
		return;
	this->hdc = GetDC(hWnd);
	this->hWnd = hWnd;
}

HWND ChildWindow::getHandle() {
	return this->hWnd;
}

void ChildWindow::setFont(HFONT font) {
	this->font = font;
	SelectObject(this->hdc, font);
}

void ChildWindow::setColor(COLORREF color) {
	this->color = color;
	SetTextColor(this->hdc, color);
}

void ChildWindow::onLButtonDown(Mode mode, LPARAM) {
	switch (mode)
	{
	case Mode::Line:
		break;
	case Mode::Rectangle:
		break;
	case Mode::Ellipse:
		break;
	case Mode::Text:
		break;
	case Mode::Select:
		break;
	default:
		break;
	}
}

void ChildWindow::onMouseMove(Mode mode, WPARAM, LPARAM) {
	switch (mode)
	{
	case Mode::Line:
		break;
	case Mode::Rectangle:
		break;
	case Mode::Ellipse:
		break;
	case Mode::Text:
		break;
	case Mode::Select:
		break;
	default:
		break;
	}
}

void ChildWindow::onLButtonUp(Mode mode) {
	switch (mode)
	{
	case Mode::Line:
		break;
	case Mode::Rectangle:
		break;
	case Mode::Ellipse:
		break;
	case Mode::Text:
		break;
	case Mode::Select:
		break;
	default:
		break;
	}
}
