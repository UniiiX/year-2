## State of student's repository at the moment of being reviewed: 
https://github.com/marynakukhta/Lab-First-2-semester-/tree/a27015c7420e457d3ef00d5e6675f605b4afc538

## Review
1. Наскільки моделі є зрозумілими, наскільки вони описують предметну область, структуру та поведінку відповідної системи?
#### Use Case:
* **Chat with one contact** - no verb. "*Start* chat with one contact"?
* **Delete from chat** - no subject. Delete what? Message?
* **Stickers** - no verb. "*Manage* stickers"?
* **Group notifications** - no verb. "*Edit* group notifications"?
* **In-app notifications** - no verb. "*Edit* in-app notifications"? 
* **Badge counter** - no verb?
* **Trending stickers** - no verb. "*Browse* trending stickers"? "*Manage* trending stickers"?
* **Masks** - no verb. "*Manage* masks"?
* **Connection type** - no verb. "*Set* connection type"?
* **Data and Storage** - no verb. "Manage Data and Storage"?
* **Appearance** - no verb. "Edit appearance"?
* **Animation** - no verb.
* **Telegram FAQ** - no verb. "*Browse* Telegram FAQ"? "*Read* Telegram FAQ"?
* **Privacy and Security** - no verb. "*Manage* Privacy and Security"?
* **Data settings** - no verb. "*Manage* data settings"?
* **Notifications(On/Off)** - no verb. "*Set* notifications on or off"?
* **Web Search**. "*Set profile photo via* web search"?
* **Enter to accont app/browser**. "*Sign in via* app/browser"?

#### Class:
* What is timestamp, text? text = string?
* What is File? No such class.
* What is time? No such class.
* What is date? No such class.

#### Activity:
* What is **Condition**?
* Logical mistake. An app can only be exited after sending message to an interlocutor?
* All in all, activity diagram is almost totally wrong/ununderstandable.

#### Communication:
* Looks ugly.

#### State:
* **Press button**. Press which button??

2. Чи є якісь аспекти, які видаються важливими, але не відображені в моделі (на діаграмах)?
* Use Case: No search? (Even though it is depicted on the Activity diagram?)
* Class Diagram: Classes timestamp, text are not depicted(are they even classes?).

3. Чи є в моделі щось зайве, якісь аспекти описані занадто детально?

4. Наскільки доцільно використані різні типи діаграм?
* State = Activity antipattern?

5. Наскільки коректно використана нотація UML, різні елементи та конектори?
#### Use Case:
Every single <<include>>, except for those between creating chats and sending a message, must be replaced with <<extend>>.
#### Class:
* "**+Scopes: array**" array of what??
* "**+Message: text**" - "+text: Message"?
* "**+Date: timestamp**" - "+timestamp: Date"?
#### Activity:
* Wrong usage of parallelization node. Log in and sign up are parallel processes?
* No guards for decision node.
* No indication that **Call** is a call behaviour action.
* Absent guard "*Valid*"
* No final node??
* What if person was already logged in before making a call? Decision node is missing?
  
#### Communication:
* "**Process answer**" but no "*Process message*"?

#### State:
* Where are all the states???
* Duplication of **Photo/Video Send** 
* **Sticker/Smile** - no verb. *Send Sticker/Smile*?

#### Sequence:
* What is **Server**? No such class on the Class Diagram?
* I like how it is depicted that chat is client-sided. (Users can delete messages only for themselves, not affecting the state of interlocutor's chat)


6. Наскільки вдалим є глосарій? Чи всі важливі поняття предметної області описано? Чи немає неоднозначностей?
* All entities from Use Case daigram are absent in the glossary, which makes some aspects hard/impossible to understand.
* No need to use word "class" at all. Client might have no idea what class is.
* What is the difference between chat and group?(Activity diagram)
* What is "**Scope**" on the class diargam?
* What is the difference between smile and emoji?(First term is present on the State diagram the other one - on the Use Case diagram)
* To sum up - awful.

7. Чи всі важливі сценарії використання описано в моделі? Наскільки зрозумілі різні сценарії, зв’язки між ними?
No search. As I've already mentioned, almost totally wrong usage of <<include>> on the Use Case diagram. 

8. Наскільки доцільним є поділ системи на частини/компоненти/модулі/...?

9. Наскільки доцільними є зв’язки між компонентами/класами/об’єктами? Чи немає занадто тісно зв’язаних компонентів?

10. Наскільки object-oriented design відповідає загальним принципам?
Class Diagram: ok.
