// 华勤科技版权所有 2010-2011
// 
// 文件名：ToolBar.h
// 功  能：工具栏控件类。
// 
// 作  者：MPF开发组
// 时  间：2010-07-02
// 
// ============================================================================

#ifndef _UITOOLBAR_H_
#define _UITOOLBAR_H_

#include <Extend/suiwgxconfig.h>
#include <System/Tools/Array.h>
#include <System/Tools/Collection.h>
#include <Extend/Controls/ToolBarPanel.h>
#include <Framework/Controls/HeaderedItemsControl.h>

namespace suic
{

class BandInfo
{
private:
    
    int _thickness;
    Array<ToolBar*> _band;
    
public:

    BandInfo()
    {
        _thickness = 0;
    }

    Array<ToolBar*>& GetBand()
    {
        return _band;
    }
    
    int GetThickness() const
    {
        return _thickness;
    }

    void SetThickness(int val)
    {
        _thickness = val;
    }
};

class ToolBarTray;

class SUIWGX_API ToolBarCollection
{
public:
    
    ToolBarCollection(ToolBarTray* parent);
    ~ToolBarCollection();

    int GetCount() const;
    ToolBar* GetToolBar(int index) const;

    int IndexOf(Object* val);
    bool Contains(Object* value);

    void AddToolBar(ToolBar* item);
    void InsertToolBar(int index, ToolBar* item);
    void RemoveToolBar(int index);
    void SetToolBar(int index, ToolBar* item);

    void Clear();

private:

    void RemoveToolBarItem(ToolBar* child);
    void AddToolBarItem(ToolBar* toolBar);

private:

    ToolBarTray* _parent;
    Array<ToolBar*> _toolBars;
};

class SUIWGX_API ToolBarTray : public FrameworkElement, public IAddChild
{
public:

    static DpProperty* OrientationProperty;

    static bool StaticInit();

    ToolBarTray();
    ~ToolBarTray();

    Orientation GetOrientation();
    void SetOrientation(Orientation val);

protected:

    void OnArrange(const fSize& arrangeSize);
    fSize OnMeasure(const fSize& constraint);

    void AddChild(Object* child);
    void AddText(String val);

    int GetVisualChildrenCount();
    Element* GetVisualChild(int index);

private:

    bool IsBandsDirty();

    void GenerateBands();
    ToolBarCollection* GetToolBars();
    BandInfo* CreateBand(int startIndex);
    int GetBandFromOffset(int toolBarOffset);

    void InsertBand(ToolBar* toolBar, int toolBarIndex);
    void InsertToolBar(ToolBar* toolBar, Array<ToolBar*>& band);

    void ExpandToolBars(Array<ToolBar*>& band, int startIndex, int endIndex, int expandAmount);

private:

    bool _bandsDirty;
    Array<BandInfo*> _bands;
    ToolBarCollection* _toolBarsCollection;
};

/// <summary>
/// ToolBar
/// </summary>
class SUIWGX_API ToolBar : public HeaderedItemsControl
{
public:
    
    static DpProperty* BandIndexProperty;
    static DpProperty* BandProperty;
    static DpProperty* HasOverflowItemsProperty;
    static DpProperty* IsOverflowItemProperty;
    static DpProperty* IsOverflowOpenProperty;
    static DpProperty* OrientationProperty;
    static DpProperty* OverflowModeProperty;

    static bool CoerceIsOverflowOpen(DpObject* d, bool val);
    static Orientation CoerceOrientation(DpObject* d, Orientation val);
    static bool CoerceToolTipIsEnabled(DpObject* d, bool val);
    static bool GetIsOverflowItem(DpObject* elem);
    static bool IsValidOverflowMode(int val);
    static void SetIsOverflowItem(DpObject* elem, Object* val);
    static void SetOverflowMode(DpObject* elem, OverflowMode mode);
    static OverflowMode GetOverflowMode(DpObject* elem);

    static void OnMouseDown(Element* sender, MouseButtonEventArg* e);
    static void OnOverflowModeChanged(DpObject* d, DpPropChangedEventArg* e);
    static void OnOverflowOpenChanged(DpObject* d, DpPropChangedEventArg* e);

    static bool StaticInit();

    ToolBar();
    virtual ~ToolBar();

    RTTIOfClass(ToolBar)

    ToolBarOverflowPanel* FindToolBarOverflowPanel();
    ToolBarPanel* FindToolBarPanel();

    void InvalidateLayout();

    int GetBand();
    void SetBand(int val);

    int GetBandIndex();
    void SetBandIndex(int val);

    bool IsOverflowOpen();
    void SetIsOverflowOpen(bool val);

protected:

    Float GetMinLength() const;
    Float GetMaxLength() const;

    ToolBarTray* GetToolBarTray();
    Orientation GetOrientation();
    ToolBarPanel* GetToolBarPanel();
    ToolBarOverflowPanel* GetToolBarOverflowPanel();

    void Close();
    void RegisterToOpenOnLoad();

    fSize OnMeasure(const fSize& constraint);
    void OnItemsChanged(NotifyCollChangedEventArg* e);
    void OnTemplateChangedInternal(FrameworkTemplate* oldTemplate, FrameworkTemplate* newTemplate);

    friend class ToolBarTray;
    friend class ToolBarPanel;
    friend class ToolBarOverflowPanel;

private:

    Float _maxLength;
    Float _minLength;

    ToolBarPanel* _toolBarPanel;
    ToolBarOverflowPanel* _toolBarOverflowPanel;
    

};

}

#endif
