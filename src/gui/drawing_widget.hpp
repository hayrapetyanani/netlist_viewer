#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "../database/project.hpp"

class drawing_widget : public QWidget
{
	private:
		QGraphicsView* m_view;
		QGraphicsScene* m_scene;
		Project* m_project;
	void refresh_scene();
	public:
		drawing_widget(QWidget* p);
};
