# UML Class Diagram — Relationships & Multiplicity

---

## 1. Relationships

### 1.1 Inheritance (Generalization) — "IS-A"
> Child **is a** type of Parent. Child inherits all parent behavior.

**Notation:** Solid line + **hollow triangle arrowhead** pointing to parent

```
Animal ◁────── Dog
```

**C++ Code:**
```cpp
class Dog : public Animal {};
```

**Example:** `Dog` IS-A `Animal`, `UPIProcessor` IS-A `PaymentGateway`

---

### 1.2 Realization (Interface Implementation) — "CAN-DO"
> Class implements an interface/abstract class.

**Notation:** Dashed line + **hollow triangle arrowhead** pointing to interface

```
«interface»
Payable ◁- - - - CreditCard
```

**C++ Code:**
```cpp
class CreditCard : public Payable {};  // Payable is pure abstract
```

**Example:** `CardProcessor` realizes `PaymentGateway` (pure virtual)

---

### 1.3 Association — "USES-A" / "KNOWS-A"
> One class **uses** another. Most general relationship.

**Notation:** Solid line, optional open arrowhead for direction

```
Customer ────────> Order
```

**C++ Code:**
```cpp
class Customer {
    Order* order;   // just knows about Order
};
```

**Example:** `Student` and `Course` — student uses/attends a course

---

### 1.4 Aggregation — "HAS-A" (Weak)
> One class **contains** another, but child **can exist independently**.

**Notation:** Solid line + **hollow diamond** on the parent side

```
ParkingSpot ◇────── Vehicle
```

**C++ Code:**
```cpp
class ParkingSpot {
    Vehicle* vehicle = nullptr;  // Vehicle exists without ParkingSpot
};
```

**Key:** Destroy `ParkingSpot` → `Vehicle` still exists  
**Example:** `Team` ◇── `Player` (player can exist without team)

---

### 1.5 Composition — "HAS-A" (Strong)
> Parent **owns** child. Child **cannot exist** without parent.

**Notation:** Solid line + **filled diamond** on the parent side

```
House ◆────── Room
```

**C++ Code:**
```cpp
class House {
    Room room;    // Room is created/destroyed WITH House
};
```

**Key:** Destroy `House` → `Room` is also destroyed  
**Example:** `Order` ◆── `OrderItem`, `Human` ◆── `Heart`

---

### 1.6 Dependency — "DEPENDS-ON"
> One class **temporarily uses** another (e.g., as method param or local var).

**Notation:** Dashed line + **open arrowhead**

```
PaymentService - - - -> PaymentGateway
```

**C++ Code:**
```cpp
class PaymentService {
    void checkOut(PaymentGateway* g) { ... }  // temporary use
};
```

**Example:** A `Report` class uses a `Printer` only to print

---

## 2. Quick Comparison Table

| Relationship | Notation | Strength | Child exists alone? | C++ hint |
|---|---|---|---|---|
| Inheritance | Solid + hollow △ | Strongest | N/A | `: public` |
| Realization | Dashed + hollow △ | Strong | N/A | `: public` (abstract) |
| Composition | Solid + filled ◆ | Strong | ❌ No | Member object (by value) |
| Aggregation | Solid + hollow ◇ | Weak | ✅ Yes | Member pointer `*` |
| Association | Solid line → | Weak | ✅ Yes | Pointer or reference |
| Dependency | Dashed line → | Weakest | ✅ Yes | Method param / local var |

---

## 3. Multiplicity (How many?)

Multiplicity is written **on both ends** of the relationship line.

### Notation Values

| Notation | Meaning |
|---|---|
| `1` | Exactly one |
| `0..1` | Zero or one (optional) |
| `*` or `0..*` | Zero or many |
| `1..*` | One or many (at least one) |
| `2..5` | Between 2 and 5 |
| `n` | Exactly n |

---

### Reading Multiplicity on a Diagram

```
ParkingLot 1 ◆──────────── 0..* ParkingSpot
```
> One `ParkingLot` has **zero or many** `ParkingSpot`s.  
> A `ParkingSpot` belongs to **exactly one** `ParkingLot`.

---

```
Student 0..* ────────────── 0..* Course
```
> A `Student` can enroll in **many** courses.  
> A `Course` can have **many** students.  
> *(Many-to-Many — usually needs a join class)*

---

```
Person 1 ◆──────────── 2..4 Limb
```
> A `Person` has **2 to 4** `Limb`s.

---

## 4. Full Example — Parking Lot Diagram

```
         «abstract»
         Vehicle
            △
     ┌──────┴──────┐
   Car           Bike

ParkingLot 1 ◆──── 0..* ParkingSpot
                              ◇
                           0..1
                           Vehicle
```

| Line | Meaning |
|---|---|
| `Vehicle △── Car` | Car IS-A Vehicle (Inheritance) |
| `ParkingLot ◆── ParkingSpot` | Lot OWNS spots (Composition) — spots die with lot |
| `ParkingSpot ◇── Vehicle` | Spot HAS a vehicle (Aggregation) — vehicle lives on |
| `1` on ParkingLot | One lot |
| `0..*` on ParkingSpot | Many spots per lot |
| `0..1` on Vehicle | A spot has 0 or 1 vehicle at a time |

---

> [!TIP]
> **Memory trick:**  
> - Filled diamond ◆ = **C**omposition = **C**hained (child dies with parent)  
> - Hollow diamond ◇ = **A**ggregation = **A**lone (child survives)

---

## 5. Association vs. Aggregation (How to Find the Difference)

### The Conceptual Hierarchy
> **Association** is the general umbrella; **Aggregation** is a specialized form of Association that adds a "Whole-Part" (Container-Content) relationship.

```text
Association (Broadest: Peers interacting)
   └── Aggregation (Whole-Part, Weak: Container & Content, survives alone)
         └── Composition (Whole-Part, Strong: Container & Content, dies with owner)
```

### Side-by-Side Comparison

| Feature | **Association** ("Uses-A" / "Knows-A") | **Aggregation** ("Has-A" / "Whole-Part") |
|---|---|---|
| **Nature** | **Peers / Equals** interacting | **Container / Content** (Whole vs Part) |
| **Concept** | Entity A simply *interacts* with or *knows* Entity B | Entity A *contains / holds* Entity B |
| **UML Symbol** | Plain line with arrow: `────────>` | Hollow diamond on container: `◇──────` |
| **Real-life Example** | **Doctor & Patient**<br>(Neither is a "part" of the other) | **Team & Players**<br>(Team is the "whole", Player is the "part") |

---

### The 2-Question Detection Test ("How to Find")

Whenever you evaluate two classes `A` and `B`, ask these two questions in order:

```mermaid
flowchart TD
    Q1{"Is A a 'Container / Whole' and B a 'Part' of it?"}
    Q1 -- "NO (They are just peers interacting)" --> ASSOC["ASSOCIATION (───>)"]
    Q1 -- "YES (Whole-Part relationship)" --> Q2{"If Container A is destroyed, does Part B survive?"}
    Q2 -- "YES (B survives on its own)" --> AGG["AGGREGATION (◇───)"]
    Q2 -- "NO (B dies with A)" --> COMP["COMPOSITION (◆───)"]
```

---

### Real Examples from Our Parking Lot System

1. **`ParkingSpot` and `Vehicle` ➔ Aggregation (`◇`)**
   - *Is spot a container for vehicle?* **YES**. The spot holds the vehicle.
   - *If the spot is demolished, does the vehicle survive?* **YES**, the vehicle just drives away.
   - **Result:** `ParkingSpot ◇────── Vehicle`

2. **`ParkingTicket` and `Vehicle` ➔ Association (`──>`)**
   - *Is a ticket a container for a vehicle?* **NO**. A ticket is a record/receipt; a vehicle is not physically part of a ticket. They simply reference each other.
   - **Result:** `ParkingTicket ────────> Vehicle`

3. **`ParkingFloor` and `ParkingSpot` ➔ Composition (`◆`)**
   - *Is floor a container for spots?* **YES**.
   - *If the floor is demolished, do spots survive?* **NO**, spots are destroyed with the floor.
   - **Result:** `ParkingFloor ◆────── ParkingSpot`


