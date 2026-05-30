# Particle Life

Simulation de particules en C++ avec SFML. Les particules obéissent à des lois physiques (gravité, friction, collisions élastiques) et sont rendues en temps réel dans une fenêtre interactive.

## Fonctionnalités

- **Physique** : gravité, friction de l'air, collisions élastiques avec restitution
- **Attraction souris** : clic gauche pour attirer les particules avec un amortissement critique
- **Intégrateurs interchangeables** : Euler et Verlet (sélectionnable via l'UI)
- **Presets de gravité** : Terre, Lune, Espace
- **Thread pool** : calcul des collisions parallélisé sur plusieurs threads
- **Spatial hashing** : grille de cellules pour éviter les comparaisons O(n²)

## Architecture

```
src/
├── entities/
│   └── particle          # Position, vitesse, masse, forme SFML
├── systems/
│   ├── grid              # Grille spatiale + détection de collisions
│   └── ui                # Interface ImGui (presets, stats)
└── core/
    ├── physics.h          # Calculs de forces (gravité, friction, impulsion)
    ├── constants.h        # Paramètres globaux (fenêtre, physique, presets)
    ├── threadPool         # Pool de threads avec condition_variable
    ├── utils.h            # ParticleState (position, vitesse, accélération)
    └── integrator/
        ├── integrator.h       # Interface IIntegrator<T>
        ├── eulerIntegrator    # Intégration d'Euler explicite
        └── verletIntegrator   # Intégration de Verlet
```

## Dépendances

| Lib | Version | Rôle |
|-----|---------|------|
| SFML | 3.0.0 | Rendu, fenêtre, événements |
| Dear ImGui | 1.91.5 | Interface utilisateur |
| ImGui-SFML | 3.0 | Pont ImGui ↔ SFML |

Toutes les dépendances sont téléchargées automatiquement via `FetchContent` au build.

## Build

```bash
cmake -B build
cmake --build build
```

Nécessite CMake ≥ 3.24 et un compilateur C++17.

## Contrôles

| Action | Effet |
|--------|-------|
| `Espace` | Spawn une particule à la position de la souris |
| `Clic gauche` | Attire les particules proches |

## Physique

### Collisions

Détection par grille spatiale : chaque particule n'est comparée qu'aux particules des cellules voisines (8-voisinage). La résolution applique une impulsion basée sur les vitesses relatives et les masses :

```
J = -(1 + e) * (v_rel · n) / (1/m_a + 1/m_b)
```

où `e` est le coefficient de restitution (`RESTITUTION = 0.8`).

### Thread Pool

Le calcul des collisions est parallélisé : chaque ligne de la grille est soumise comme une tâche indépendante au pool. Un `condition_variable` notifie le thread principal quand toutes les tâches sont terminées.
