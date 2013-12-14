#include <QVBoxLayout>
#include <QGraphicsEllipseItem>
#include <iostream>

#include "drawing_widget.hpp"
#include "../database/project.hpp"

drawing_widget::drawing_widget(QWidget* p = NULL)
    : QWidget(p)
	, m_project(Project::get())
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
    
    Project::edges e = m_project->get_edges();
    for(size_t i = 0; i < e.size(); ++i) {
        node* node1 = e[i]->firstNode();
        node* node2 = e[i]->secondNode();
        std::cout << node1->get_x() + 10 <<" " << node1->get_y() + 10 << " " << node2->get_x() << " " <<  node2->get_y() << std::endl;
        m_scene->addLine(node1->get_x() + 10, node1->get_y() + 10, 
                node2->get_x() + 10, node2->get_y() + 10);
    }
//    QObject::connect(m_scene, SIGNAL(changed(const QList<QRectF> &)), this, SLOT(refresh_scene()));
}
