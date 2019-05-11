#pragma once

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class PageButton : public QToolButton
{

public:

	explicit PageButton(QString pic_name, QWidget *parent = 0);
	~PageButton();
	void setMousePress(bool mouse_press);

protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);

public:

	bool mouse_over;
	bool mouse_press;
};



