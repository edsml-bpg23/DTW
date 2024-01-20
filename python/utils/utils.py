import logging

def init_logging() -> None:
    """
    Initialise the logging configuration.
    """
    logging.basicConfig(
        format="%(asctime)s [%(name)s] %(levelname)s: %(message)s",
        level=logging.INFO,
        force=True,
    )
