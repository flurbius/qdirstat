/*
 *   File name: DirTreeView.h
 *   Summary:	Tree view widget for directory tree
 *   License:	GPL V2 - See file LICENSE for details.
 *
 *   Author:	Stefan Hundhammer <Stefan.Hundhammer@gmx.de>
 */

#ifndef DirTreeView_h
#define DirTreeView_h


#include <QTreeView>


/**
 * Tree view widget for the QDirStat directory tree.
 *
 * This is a thin wrapper around TreeView that takes care about basic setup and
 * configuration of the tree view and adds support for synchronizing current /
 * selected items between the DirTree, the DirTreeMap and this DirTreeView.
 *
 * The Qt model / view abstraction is kept up as good as possible, but this
 * widget is really meant to be used with a QDirStat::DirTreeModel and not just
 * any random subclass of QAbstractItemModel.
 **/
namespace QDirStat
{
    class PercentBarDelegate;
    class SelectionModelProxy;
    class CleanupCollection;


    class DirTreeView: public QTreeView
    {
	Q_OBJECT

    public:

	/**
	 * Constructor
	 **/
	DirTreeView( QWidget * parent = 0 );

	/**
	 * Destructor
	 **/
	virtual ~DirTreeView();

	/**
	 * Set the cleanup collection. If set, all cleanup actions from that
	 * collection will be added to the item context menu.
	 **/
	void setCleanupCollection( CleanupCollection * collection )
	    { _cleanupCollection = collection; }

	/**
	 * Return the cleanup collection or 0 if it is not set.
	 **/
	CleanupCollection * cleanupCollection() const { return _cleanupCollection; }

#if 0
	/**
	 * Set the selection model.
	 *
	 * Reimplemented from QTreeView to use a SelectionModelProxy.
	 **/
	virtual void setSelectionModel( QItemSelectionModel * selectionModel ) Q_DECL_OVERRIDE;
#endif

    protected slots:

	/**
	 * Post a context menu for the item at 'pos'.
	 **/
	void contextMenu( const QPoint & pos );

    protected:

	/**
	 * Change the current item. Overwritten from QTreeView to make sure
	 * the branch of the new current item is expanded and scrolled to
	 * the visible area.
	 **/
	virtual void currentChanged( const QModelIndex & current,
				     const QModelIndex & oldCurrent ) Q_DECL_OVERRIDE;

	// Data members

	PercentBarDelegate	* _percentBarDelegate;
	CleanupCollection	* _cleanupCollection;
#if 0
	SelectionModelProxy	* _selectionModelProxy;
#endif

    };	// class DirTreeView

}	// namespace QDirStat


#endif	// DirTreeView_h
