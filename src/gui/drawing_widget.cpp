#include "drawing_widget.hpp"
#include <QVBoxLayout>
#include <QGraphicsEllipseItem>

drawing_widget::drawing_widget(QWidget* p)
    :QWidget(p)
	,m_project(Project::get())
{
	m_scene = new QGraphicsScene();
	refresh_scene();

	QVBoxLayout* l = new QVBoxLayout(this);

	m_view = new QGraphicsView(m_scene);

	l->addWidget(m_view);
}

void 
drawing_widget::refresh_scene()
{
	Project::nodes a = m_project->get_nodes();
	for(size_t i = 0; i < a.size(); ++i) {
		QGraphicsEllipseItem* j = 
			m_scene->addEllipse(QRectF(a[i]->get_x(), 
						a[i]->get_y(), 20, 20));

		j->setFlag(QGraphicsItem::ItemIsMovable);
	}
}
