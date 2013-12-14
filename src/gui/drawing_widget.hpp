#ifndef DRAWING_WIDGET_H
#define DRAWING_WIDGET_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class Project;

class drawing_widget : public QWidget
{
    Q_OBJECT
	private:
		QGraphicsView* m_view;
		QGraphicsScene* m_scene;
		Project* m_project;
    public slots:
	    void refresh_scene();
	public:
		drawing_widget(QWidget* p);
};
#endif
