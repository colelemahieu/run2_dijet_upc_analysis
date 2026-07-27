# HIN-24-022 Analysis documentation

### Links
- [CADI](https://cmsfence.cern.ch/alcm/cmsanalysis/details/ancode=HIN-24-022)
- [Twiki](https://twiki.cern.ch/twiki/bin/viewauth/CMS/ReviewPbPb2018UPCDijets?extralog=-%20caching%20topic)
- [PubTalk](https://cms-pub-talk.web.cern.ch/c/hin/hin-24-022/709)
- [Google Doc Approval Document](https://docs.google.com/document/d/1ONnxC_hpBWyAXRdlPLtoRCERCwto8VxcuF4oUGW-TkE/edit?tab=t.0#heading=h.kmrxuwz216y0)

### Overview
This repository is organized into the following stages:

**1. Produce Forest files**
   - **Data:** `Data/produceForest/`
   - **MC:** `MC/produceMC/`

**2. Skim Forest files**
   - **Data:** `Data/skimForest/`
   - **MC:** `MC/skimMC/`

**3. Create analysis histograms**
   - **Data:** `Data/getData_hists/`
   - **MC:** `MC/getMC_hists/`

   This step:
   - applies additional event selections,
   - calculates `v₂ = ⟨cos(2φ)⟩`,
   - saves the output histograms.

**4. Produce plots:** `Plots`
   - makes resolution plots, general AN plots, and comparison plots

**5. Unfolding:**
   - **2D unfolding, phi vs QT:** `Unfolding/unfold_qt/`
   - **2D unfolding, phi vs rapidity:** `Unfolding/unfold_rap/`
   - These directories contain examples of scripts used for 2D unfolding with RooUnfold.

**6. Produce systematic and result plots**
   - **v₂ and v₄ vs QT:** `Systematics_and_Results/phi_vs_qt/`
   - **v₂ and v₄ vs rapidity:** `Systematics_and_Results/phi_vs_rap/`

   This step:
   - calculates average bin systematics and adds them in quadrature
   - makes systematic plots and final result plots
   - makes plots summarizing systematic contributions


