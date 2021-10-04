ESC 2021 Challenge Description
==============================

This year's challenge will focus on **side channel and fault injection attacks** targeting hardware platforms that can exfiltrate sensitive data. Competitors will demonstrate their skills using the popular **Chipwhisperer** platform in a red team/blue team scenario to either launch or mitigate these powerful attacks.

ESC21 consists of **two tracks**: a **research** track and a **technical** track. The research track focuses on developing side channel and fault injection attack mitigation strategies to secure target applications. The
technical track focuses on exploiting these vulnerabilities to launch attacks against a series of challenge applications running on the provided hardware platform.

See the [grading details](#evaluation-and-grading-policies) below for more information on evaluation.


## Challenge structure

The ESC21 competition is divided into three phases:

1. A preliminary **qualification phase**, where teams must compile and submit a short written report. Teams applying
for the research track should investigate mitigation techniques and what strategies they plan to use for the
final phase while technical track teams should outline techniques that they will potentially employ to solve
the series of challenges in the final phase.

2. A **final phase**, where qualified teams are invited to the *CSAW virtual event* of their region to present and demonstrate either their attack implementations (technical) or their mitigation strategies (research) on the Chipwhisperer board provided by the organizers.

3. A **timed-attack/fortify phase**, where qualified teams will be provided with a special challenge program on the day of the virtual ESC finals in their region. The contestants will then race to solve the challenge: technical track teams will attempt to mount exploits while research track teams will investigate the vulnerabilities and apply patches.

See below for more details on the requirements of each phase.


### Qualification Phase

For the qualification phase, teams should submit a **short report** that outlines approaches and techniques (not only one approach/technique) to perform side channel and fault injection attacks (technical) or to mitigate them (research). To that end, the report should also explore existing techniques on the topic, focusing on (but not necessarily limited to) attacking/mitigating attacks against cryptographic hardware. The best approaches will include a discussion of existing techniques, a clear outline of attack methodologies, and a discussion of how the methodologies will be applied in the final phase of the competition.

Qualification phase reports will be evaluated by a team of experts, and will take into account the **correctness** and **creativity** of proposed techniques, as well as the completeness and quality of the compiled report.

### Final Phase

The top teams of each region (US-Canada, Europe, MENA, India) will qualify for the final phase, which will require **implementing** and **demonstrating** side-channel and fault injection attacks (technical), or **mitigating** such attacks (research), on an STM microcontroller using the ChipWhisperer Nano board.
Additional details about the final phase are available [here](final-phase.md).
The teams should compose a final report detailing their approaches. The definitive goal is to demonstrate their methods during the finals.

### Timed-Attack Phase

Details will be released before the ESC 2021 finals.

## Evaluation and Grading Policies

The evaluation of the finalists from both tracks will be the responsibility of a team of **expert judges** in each region. During the virtual finals, each team should be able to *answer the questions* posed by the judges and *demonstrate their methods*. Furthermore, the finalists will prepare a **short, high-level 10-minute pre-recorded video** that will air on the day of the finals, as well as a **technical poster or presentation slides** (with additional/orthogonal content, and minimual overlap to the pre-recorded video) to present live to the expert judges, complementing their submitted **final report**. During the virtual finals, each team should be ready to demonstrate their solved challenges.

The final phase will be graded as follows:
- 50% of the final score will be **correctness**. The points awarded in this section are based on successfully solving (technical) or mitigating (research) the provided challenges and depend on the difficulty of each challenge. The awarded points will be determined systematically by the global organizers and the expert judges. 
- 20% of the score will be **performance** and **efficiency**. Performance will be evaluated by the panel of expert judges and will encompass the techniques that the participants utilize to address the challenges. For example, utilizing an exhaustive test for every possible solution would be rated as very inefficient, whereas a solution that examines a process and can determine an exact solution would be rated as very efficient.
- 30% of the score will be the **quality** of the final deliverables (report, pre-recorded video, and judges presentation or poster). The final deliverables will be graded by the judges panel based on organization, clearness of presentation, and detail of explanations.

 **Note 1: The use of software tools requiring a paid license or a demo license of a non-free tool is not allowed.**

 **Note 2: Valid solutions must exploit only side channel or fault injection vulnerabilities.**


You can refer to the [deliverables page](deliverables.md) for more details on the qualification and final phase deliverables.


To find more information regarding how to register and participate click [here](logistics.md).
