/////////////////////////////////////////////////////////////////////////////
// Name:        convertfunctor.h
// Author:      David Bauer
// Created:     2023
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_CONVERTFUNCTOR_H__
#define __VRV_CONVERTFUNCTOR_H__

#include "functor.h"

namespace vrv {

//----------------------------------------------------------------------------
// ConvertToPageBasedFunctor
//----------------------------------------------------------------------------

/**
 * This class converts all top-level containers (section, endings) and editorial elements to milestone elements.
 */
class ConvertToPageBasedFunctor : public MutableFunctor {
public:
    /**
     * @name Constructors, destructors
     */
    ///@{
    ConvertToPageBasedFunctor(Page *page);
    virtual ~ConvertToPageBasedFunctor() = default;
    ///@}

    /*
     * Abstract base implementation
     */
    bool ImplementsEndInterface() const override { return true; }

    /*
     * Functor interface
     */
    ///@{
    FunctorCode VisitEditorialElement(EditorialElement *editorialElement) override;
    FunctorCode VisitEditorialElementEnd(EditorialElement *editorialElement) override;
    FunctorCode VisitEnding(Ending *ending) override;
    FunctorCode VisitEndingEnd(Ending *ending) override;
    FunctorCode VisitMeasure(Measure *measure) override;
    FunctorCode VisitMdiv(Mdiv *mdiv) override;
    FunctorCode VisitMdivEnd(Mdiv *mdiv) override;
    FunctorCode VisitScore(Score *score) override;
    FunctorCode VisitScoreEnd(Score *score) override;
    FunctorCode VisitScoreDef(ScoreDef *scoreDef) override;
    FunctorCode VisitSection(Section *section) override;
    FunctorCode VisitSectionEnd(Section *section) override;
    FunctorCode VisitSystemElement(SystemElement *systemElement) override;
    ///@}

protected:
    //
private:
    //
public:
    //
private:
    // The system we are moving the content to
    System *m_currentSystem;
    // The page being processed
    Page *m_page;
};

//----------------------------------------------------------------------------
// ConvertToCastOffMensuralFunctor
//----------------------------------------------------------------------------

/**
 * This class converts mensural MEI into cast-off (measure) segments looking at the barLine objects.
 * Segment positions occur where a barLine is set on all staves.
 */
class ConvertToCastOffMensuralFunctor : public DocFunctor {
public:
    /**
     * @name Constructors, destructors
     */
    ///@{
    ConvertToCastOffMensuralFunctor(Doc *doc, System *targetSystem, IntTree *layerTree);
    virtual ~ConvertToCastOffMensuralFunctor() = default;
    ///@}

    /*
     * Abstract base implementation
     */
    bool ImplementsEndInterface() const override { return false; }

    /*
     * Setter for staff @n
     */
    ///@{
    void AddStaffN(int staffN) { m_staffNs.push_back(staffN); }
    void ClearStaffNs() { m_staffNs.clear(); }
    ///@}

    /*
     * Functor interface
     */
    ///@{
    FunctorCode VisitBarLine(BarLine *barLine) override;
    FunctorCode VisitLayer(Layer *layer) override;
    FunctorCode VisitMeasure(Measure *measure) override;
    FunctorCode VisitObject(Object *object) override;
    FunctorCode VisitScoreDef(ScoreDef *scoreDef) override;
    FunctorCode VisitStaff(Staff *staff) override;
    FunctorCode VisitSystemElement(SystemElement *systemElement) override;
    ///@}

protected:
    //
private:
    //
public:
    //
private:
    // The staff @n for finding splitting bar lines
    std::vector<int> m_staffNs;
    // The content layer from which we are copying the elements
    Layer *m_contentLayer;
    // The target system, measure, staff & layer
    System *m_targetSystem;
    Measure *m_targetMeasure;
    Staff *m_targetStaff;
    Layer *m_targetLayer;
    // A sub-system (e.g., section) to add measure segments
    System *m_targetSubSystem;
    // A counter for segments in the sub-system (section)
    int m_segmentIdx;
    // The total number of segments (previous sections)
    int m_segmentTotal;
    // An IntTree for processing by layer
    IntTree *m_layerTree;
};

} // namespace vrv

#endif // __VRV_CONVERTFUNCTOR_H__
