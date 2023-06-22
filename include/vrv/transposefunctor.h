/////////////////////////////////////////////////////////////////////////////
// Name:        transposefunctor.h
// Author:      David Bauer
// Created:     2023
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_TRANSPOSEFUNCTOR_H__
#define __VRV_TRANSPOSEFUNCTOR_H__

#include "functor.h"

namespace vrv {

//----------------------------------------------------------------------------
// TransposeFunctor
//----------------------------------------------------------------------------

/**
 * This class transposes the content.
 */
class TransposeFunctor : public DocFunctor {
public:
    /**
     * @name Constructors, destructors
     */
    ///@{
    TransposeFunctor(Doc *doc, Transposer *transposer);
    virtual ~TransposeFunctor() = default;
    ///@}

    /*
     * Abstract base implementation
     */
    bool ImplementsEndInterface() const override { return true; }

    /*
     * Setter for various properties
     */
    ///@{
    void SetTransposition(const std::string &transposition) { m_transposition = transposition; }
    void SetSelectedMdivID(const std::string &selectedID) { m_selectedMdivID = selectedID; }
    void SetTransposeToSoundingPitch() { m_transposeToSoundingPitch = true; }
    ///@}

    /*
     * Functor interface
     */
    ///@{
    FunctorCode VisitHarm(Harm *harm) override;
    FunctorCode VisitKeySig(KeySig *keySig) override;
    FunctorCode VisitMdiv(Mdiv *mdiv) override;
    FunctorCode VisitNote(Note *note) override;
    FunctorCode VisitPageMilestone(PageMilestoneEnd *pageMilestoneEnd) override;
    FunctorCode VisitRest(Rest *rest) override;
    FunctorCode VisitScore(Score *score) override;
    FunctorCode VisitScoreDef(ScoreDef *scoreDef) override;
    FunctorCode VisitScoreDefEnd(ScoreDef *scoreDef) override;
    FunctorCode VisitStaff(Staff *staff) override;
    FunctorCode VisitStaffDef(StaffDef *staffDef) override;
    FunctorCode VisitSystem(System *system) override;
    ///@}

protected:
    //
private:
    //
public:
    //
protected:
    // The transposer
    Transposer *m_transposer;
    // The current KeySig for staffN (ScoreDef key signatures are mapped to -1)
    std::map<int, const KeySig *> m_keySigForStaffN;

private:
    // The transposition to be applied
    std::string m_transposition;
    // The mdiv selected for transposition
    std::string m_selectedMdivID;
    // The list of current (nested) mdivs
    std::list<std::string> m_currentMdivIDs;
    // Transpose to sounding pitch by evaluating @trans.semi ?
    bool m_transposeToSoundingPitch;
    // The transposition interval for staffN
    std::map<int, int> m_transposeIntervalForStaffN;
};

//----------------------------------------------------------------------------
// TransposeToSoundingPitchFunctor
//----------------------------------------------------------------------------

/**
 * This class transposes the content to sounding pitch (by evaluating @trans.semi).
 */
class TransposeToSoundingPitchFunctor : public TransposeFunctor {
public:
    /**
     * @name Constructors, destructors
     */
    ///@{
    TransposeToSoundingPitchFunctor(Doc *doc, Transposer *transposer);
    virtual ~TransposeToSoundingPitchFunctor() = default;
    ///@}

    /*
     * Abstract base implementation
     */
    bool ImplementsEndInterface() const override { return true; }

    /*
     * Functor interface
     */
    ///@{
    FunctorCode VisitMdiv(Mdiv *mdiv) override;
    FunctorCode VisitScore(Score *score) override;
    FunctorCode VisitScoreDef(ScoreDef *scoreDef) override;
    FunctorCode VisitScoreDefEnd(ScoreDef *scoreDef) override;
    FunctorCode VisitStaff(Staff *staff) override;
    FunctorCode VisitStaffDef(StaffDef *staffDef) override;
    ///@}

protected:
    //
private:
    //
public:
    //
private:
    // The transposition interval for staffN
    std::map<int, int> m_transposeIntervalForStaffN;
};

} // namespace vrv

#endif // __VRV_TRANSPOSEFUNCTOR_H__
